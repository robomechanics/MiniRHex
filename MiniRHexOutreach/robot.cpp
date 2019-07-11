#include "robot.h"
#include "conversions.h"
#include "Arduino-compatibles.h"
#include "usb_serial.h"
#include "HardwareSerial.h"

Robot::Robot(Dynamixel *dxl) : Dxl(dxl) {
    dead_buffer = 40;

    legs_active = 6;

    kp_hold = 0.008;
    kd_hold = 1.0;

    packet_length = 2*legs_active;
    // packet[packet_length];

    low_battery = 1; // 1 = red, 3 = yellow, 2 = green
    prev_low_battery = 0;

    legs[0] = Leg(0, 0, stand_gait, 0, false, false, false); // this leg is a spacer in the array, only used to make each leg's index be equal to its number
    legs[1] = Leg(1, 0, stand_gait, 0, false, false, false);
    legs[2] = Leg(2, 0, stand_gait, 0, false, false, false);
    legs[3] = Leg(3, 0, stand_gait, 0, false, false, false);
    legs[4] = Leg(4, 0, stand_gait, 0,  true, false, false);
    legs[5] = Leg(5, 0, stand_gait, 0,  true, false, false);
    legs[6] = Leg(6, 0, stand_gait, 0,  true, false, false);
}

Robot::Robot(float set_zeros[6], Dynamixel *dxl) : Dxl(dxl) {
    zeros = set_zeros;

    dead_buffer = 40;

    legs_active = 6;

    kp_hold = 0.008;
    kd_hold = 1.0;

    packet_length = 2*legs_active;
    // packet[packet_length];

    low_battery = 1; // 1 = red, 3 = yellow, 2 = green
    prev_low_battery = 0;

    legs[0] = Leg(0, 0, stand_gait,     0,    false, false, false); // this leg is a spacer in the array, only used to make each leg's index be equal to its number
    legs[1] = Leg(1, 0, stand_gait, zeros[0], false, false, false);
    legs[2] = Leg(2, 0, stand_gait, zeros[1], false, false, false);
    legs[3] = Leg(3, 0, stand_gait, zeros[2], false, false, false);
    legs[4] = Leg(4, 0, stand_gait, zeros[3],  true, false, false);
    legs[5] = Leg(5, 0, stand_gait, zeros[4],  true, false, false);
    legs[6] = Leg(6, 0, stand_gait, zeros[5],  true, false, false);
}

void Robot::setup() {
    Dxl->begin(3); // baudrate set to 1 Mbps (max)
    int t_start = millis();
    for (int i = 1; i <= legs_active; i++) { // legs stored at their index
        Dxl->wheelMode(legs[i].id); // change servo to wheel mode
        legs[i].updateGait(stand_gait, t_start); // set initial parameters, initial_gait in gait_parameters
    }
}

int Robot::incrementGait() {
    gait_idx = (gait_idx + 1) % TOTAL_GAITS;
    return updateGait(all_gaits[gait_idx]);
}

int Robot::updateGait(Gait gait) {
    int t_start = millis();
    for(int i = 1; i <= legs_active; i++) {
      legs[i].updateGait(gait, t_start);
    }
    return gait_idx;
}

int Robot::checkBattery() {
    voltage = 0;
    for (int i = 1; i <= legs_active; i++) {
      voltage_check = Dxl->readByte(legs[1].id, PRESENT_VOLTAGE);
      if (voltage_check > voltage) voltage = voltage_check;
    }
    SerialUSB.println(voltage);

    if (voltage > 73) { //green
      low_battery = 2;
    }
    else if (voltage < 71) { //red
      low_battery = 1;
    }
    else{
      low_battery = 3; //yellow
    }

    if (prev_low_battery != low_battery) {
        SerialUSB.println("Should switch led color here");
        for (int i = 1; i <= legs_active; i++) {
          Dxl->writeByte(legs[i].id, LED, low_battery);
        }
    }
    return voltage;
}

float Robot::pd_calc(float theta_act, float theta_des,
                        float v_act, float v_des,
                        float kp, float kd)
{
  float diff = fmod(theta_des - theta_act, theta_circle);
  float shortest_distance = theta_circle/2 - fabs(fabs(diff) - theta_circle/2);
  float dtheta = fmodf(diff + theta_circle, theta_circle) < theta_circle/2 ? shortest_distance : -shortest_distance;
  float dv = (v_des - v_act);
  return kp * dtheta + kd * dv;
}

void Robot::update() {
    word packet[packet_length];

    // primary for-loop
    for(int i = 1; i <= legs_active; i++) {
        packet[(i-1) * 2] = legs[i].id;
        actual_p = Dxl->readWord(legs[i].id, PRESENT_POS);
        actual_theta = P_to_Theta(actual_p); // converted to degrees, relative to leg
        actual_vel = dynV_to_V(Dxl->readWord(legs[i].id, PRESENT_SPEED)); // converted to degrees/ms, relative to leg

        if (!legs[i].deadzone) {
            if (actual_p == 0 || actual_p == 1023) { //entering deadzone
                legs[i].deadzone = true;
                if (actual_p == 0) legs[i].dead_from_neg = true;
                else legs[i].dead_from_neg = false;
                continue;
            }

            if (legs[i].gait.id == 0) { // standing or sitting
                if (legs[i].right_side) {
                    desired_theta = Theta_to_ThetaR(legs[i].desired_theta);
                }
                else {
                    desired_theta = legs[i].desired_theta;
                }
                actual_theta = actual_theta - legs[i].zero; //zero out leg thetas, accounts for small servo irregularities
                control_signal = pd_calc(actual_theta, desired_theta, actual_vel, 0, kp_hold, kd_hold);
        }
        else { // walking, turning
            // compute absolute desired values (theta and velocity) from clock time
            legs[i].getDesiredVals(millis());
            // translate theta and v to relative (left and right)
            if (legs[i].right_side) {
                desired_vel = -legs[i].global_velocity; //relative
                desired_theta = Theta_to_ThetaR(legs[i].global_theta); // relative
            }
            else { // left side, relative is same as global
                desired_vel = legs[i].global_velocity;
                desired_theta = legs[i].global_theta;
            }
            actual_theta = actual_theta - legs[i].zero;

            control_signal = pd_calc(actual_theta, desired_theta, actual_vel, desired_vel, legs[i].kp, legs[i].kd);
        }

        int new_vel = V_to_dynV(actual_vel + control_signal);
            packet[(i-1) * 2 + 1] = new_vel;
        }

        else { //deadzone
            if ((actual_p > 0) & (actual_p < dead_buffer) || (actual_p < 1023) & (actual_p > 1023 -dead_buffer)) { //exiting deadzone
              legs[i].deadzone = false;
            }
            float signed_recovery_speed = legs[i].dead_from_neg == true ? -legs[i].recovery_speed : legs[i].recovery_speed;
            packet[(i-1) * 2 + 1] = V_to_dynV(signed_recovery_speed);
        }
    }

    Dxl->syncWrite(MOVING_SPEED, 1, packet, packet_length); //simultaneously write to each of 6 servoes with updated commands
}

void Robot::jumpReady() {
  int t_start = millis();
  for (int i = 1; i <= legs_active; i++) {
    legs[i].setDesiredTheta(90);
    legs[i].updateGait(stand_gait, t_start);
  }
  SerialUSB.println("JUMP READY");
}

void Robot::jump() {
  int t_start = millis();
  while (millis() - t_start < 900) {
    SerialUSB.println(t_start - millis());
    if (millis() - t_start > 0) {
      Dxl->writeWord(1, MOVING_SPEED, 1023);
      Dxl->writeWord(4, MOVING_SPEED, 2047);
    }
    if (millis() - t_start > 100) {
      Dxl->writeWord(2, MOVING_SPEED, 1023);
      Dxl->writeWord(5, MOVING_SPEED, 2047);
    }
    if (millis() - t_start > 190) {
      Dxl->writeWord(3, MOVING_SPEED, 1023);
      Dxl->writeWord(6, MOVING_SPEED, 2047);
    }
  }
  for (int i = 1; i <= legs_active; i++) {
    legs[i].desired_theta = 0;
    legs[i].updateGait(stand_gait, t_start);
  }
}

void Robot::checkForBT() {
  // bluetooth control
  if (Serial2.available()) {
    char a = (char)(Serial2.read());
    SerialUSB.println(a);
    int bt_gait_idx = -1;
    switch (a) {
    case 'q':
      bt_gait_idx = 0;
      break; //stand
    case 'w':
      bt_gait_idx = 1;
      break; //forwards
    case 's':
      bt_gait_idx = 2;
      break; //reverse
    case 'a':
      bt_gait_idx = 3;
      break; //left
    case 'd':
      bt_gait_idx = 4;
      break; //right
    case 'e':
      bt_gait_idx = 5;
      break;
    case 'x':
      jumpReady();
      break;
    case 'j':
      jump();
      break;
    }

    if (bt_gait_idx != -1) {
      int t_start = millis();
      gait_idx = bt_gait_idx;
      updateGait(all_gaits[gait_idx]);
    }
  }
}

void Robot::printServoPositions() {
    for (int i = 1; i < 7; i++){
        SerialUSB.print(i);
        SerialUSB.print(": ");
        SerialUSB.println(P_to_Theta(Dxl->readWord(i, PRESENT_POS)));
    }
}
