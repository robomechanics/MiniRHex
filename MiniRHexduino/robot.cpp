#include "robot.h"
#include "conversions.h"

//int tail_pos = 0; 
int packet_pos[2];
int count = 0;
int timeBuffer = 10; //milliseconds

Robot::Robot(Dynamixel * dxl) : Dxl(dxl)
{
  legs_active = 6;
  packet_length = 2*legs_active;

  legs[0] = Leg(1, 0, 0, 0, 0, stand_gait, 0, false, false, false);
  legs[1] = Leg(2, 1, 0, 0, 0, stand_gait, 0, false, false, false);
  legs[2] = Leg(3, 2, 0, 0, 0, stand_gait, 0, false, false, false);
  legs[3] = Leg(4, 3, 0, 0, 0, stand_gait, 0,  true, false, false);
  legs[4] = Leg(5, 4, 0, 0, 0, stand_gait, 0,  true, false, false);
  legs[5] = Leg(6, 5, 0, 0, 0, stand_gait, 0,  true, false, false);
}

void Robot::startup()
{
  Dxl->begin(3); // baudrate set to 1 Mbps (max)
  unsigned long t_start = millis();
  for (int i = 0; i < legs_active; i++) { // legs stored at their index
    legs[i].updateGait(stand_gait, t_start); // set initial parameters, initial_gait in gait_parameters
  }
  currGait = stand_gait; 
}

int Robot::incrementGait()
{
  gait_idx = (gait_idx + 1) % TOTAL_GAITS;
  return updateGait(gait_order[gait_idx]);
}

int Robot::updateGait(Gait gait)
{
  int t_start = millis();
  for(int i = 0; i < legs_active; i++) {
    legs[i].updateGait(gait, t_start);
  }
  currGait = gait_order[gait_idx]; 
  int packet[] = {1,0,2,0,3,0,4,0,5,0,6,0};
  int packetTail[] = {7,512}; 
  
  Dxl->syncWrite(30, 1, packet, packet_length);
  Dxl->syncWrite(30, 1, packetTail, 2);
  delay(100);
  return gait_idx;
}

unsigned short Robot::checkBattery()
{
  for (int i = 0; i < legs_active; i++) {
    float voltage_check = Dxl->getVolt(legs[i].id);
    if (voltage_check > voltage) {
      voltage = voltage_check / 10;
    }
  }

  Serial.print("Current Voltage: ");
  Serial.print(voltage);
  Serial.println("V");

  if (voltage > 7.3) { // green
    low_battery = 2;
  }
  else if (voltage < 7.1) { // red
    low_battery = 1;
    Serial.println("Voltage Low!");
  }
  else {
    low_battery = 3; // yellow
  }

  if (prev_low_battery != low_battery) {
    for (int i = 0; i < legs_active; i++) {
      Dxl->writeByte(legs[i].id, LED, low_battery);
    }
  }

  prev_low_battery = low_battery;

  return voltage;
}

float Robot::pd_calc(float theta_act, float theta_des,
                     float v_act, float v_des,
                     float kp, float kd)
{
  float diff = fmod(theta_des - theta_act, theta_circle);
  float shortest_distance = theta_circle/2 - fabs(fabs(diff) - theta_circle/2);
  float dtheta = (fmodf(diff + theta_circle, theta_circle) < theta_circle/2) ? shortest_distance : -shortest_distance;
  float dv = (v_des - v_act);
  return kp * dtheta + kd * dv;
}

void Robot::update_leg_params()
{
  for(int i = 0; i < legs_active; i++) {
    int pos = Dxl->getPosition(legs[i].id);
    if (pos != 65535) legs[i].position = pos;
    legs[i].velocity = Dxl->getSpeed(legs[i].id);
  }
}

void Robot::update()
{
  update_leg_params();
  word packet[packet_length];
  int curr_t; //so it can be used outside the for loop
  for(int i = 0; i < legs_active; i++) {
    packet[2*i] = legs[i].id;

    int actual_p = legs[i].position;
    float actual_theta = P_to_Theta(actual_p); // converted to degrees, relative to leg
    float actual_vel = dynV_to_V(legs[i].velocity); // converted to degrees/ms, relative to leg

    if (!legs[i].deadzone) {
      if (actual_p == 0 || actual_p == 1023) { // entering deadzone
        legs[i].deadzone = true;
        if (actual_p == 0) legs[i].dead_from_neg = true;
        else legs[i].dead_from_neg = false;
        continue;
      }

      curr_t = millis(); // used to be int curr_t = millis()
      float control_signal = 0;
      float desired_theta = 0;
      float desired_vel = 0;
      if (legs[i].gait.id == 0) { // standing or sitting
        if (legs[i].right_side) {
            desired_theta = Theta_to_ThetaR(legs[i].desired_theta);
        }
        else {
            desired_theta = legs[i].desired_theta;
        }
        actual_theta = actual_theta - legs[i].zero; // zero out leg thetas, accounts for small servo irregularities
        control_signal = pd_calc(actual_theta, desired_theta, actual_vel, 0, kp_hold, kd_hold);
      }
      else { // walking, turning
        // compute absolute desired values (theta and velocity) from clock time
        legs[i].getDesiredVals(curr_t);
        // translate theta and v to relative (left and right)
        if (legs[i].right_side) {
          desired_vel = -legs[i].global_velocity; // relative
          desired_theta = Theta_to_ThetaR(legs[i].global_theta); // relative
        }
        else { // left side, relative is same as global
          desired_vel = legs[i].global_velocity;
          desired_theta = legs[i].global_theta;
        }
        actual_theta = actual_theta - legs[i].zero;
        control_signal = pd_calc(actual_theta, desired_theta, actual_vel, desired_vel, legs[i].kp, legs[i].kd);
      }
      packet[2*i + 1] = V_to_dynV(actual_vel + control_signal);
    }
    else { // deadzone
      if ((actual_p > 0) && (actual_p < dead_buffer) || (actual_p < 1023) && (actual_p > 1023 - dead_buffer)) { // exiting deadzone
        legs[i].deadzone = false;
      }
      float signed_recovery_speed = legs[i].dead_from_neg ? -legs[i].recovery_speed : legs[i].recovery_speed;
      packet[2*i + 1] = V_to_dynV(signed_recovery_speed);
    }
  }

  //int curr_t = millis();//redefine curr_t for more accuracy
  //start appending tail stuff
  tGait curr_tgait = currGait.tgait; 
  float period = curr_tgait.period; 
  int elapsed_time = curr_t - legs[0].startMillis; 
  int tempCount;
  tempCount = elapsed_time/period; 
  if(elapsed_time>curr_tgait.initial_delay)
  {
    if(tempCount>curr_tgait.count && curr_tgait.num_locs != 1)//elapsed_time///elapsed_time%period<=timeBuffer || period - (elapsed_time%period)<=timeBuffer)
    {
      curr_tgait.count = tempCount; 
      if(curr_tgait.count!=1)
      {
        curr_tgait.curr_loc_ind = curr_tgait.curr_loc_ind + curr_tgait.phase_inc; 
      }
      if((curr_tgait.curr_loc_ind == curr_tgait.num_locs - 1 || curr_tgait.curr_loc_ind == 0) && curr_tgait.count!=1)
      {
        curr_tgait.phase_inc = -1*curr_tgait.phase_inc; 
        Serial.println("I should be multiplying by -1: ");
        Serial.println(curr_tgait.phase_inc); 
      }
    
    }
  }
  packet_pos[0] = 7;
  packet_pos[1] = curr_tgait.locations[curr_tgait.curr_loc_ind];
  currGait.tgait = curr_tgait; //update the currentGait property 
  Serial.print("Send Tail to Position: ");
  Serial.println(curr_tgait.locations[curr_tgait.curr_loc_ind]); 
  Dxl->syncWrite(30, 1, packet_pos, 2);
  Dxl->syncWrite(MOVING_SPEED, 1, packet, packet_length); //simultaneously write to each of 6 servoes with updated commands
}

void Robot::checkForBT()
{
  // bluetooth control
  if (Serial2.available()) {
    char a = (char)(Serial2.read());

    if (0x30 <= a && a <= 0x77) { // for compatibility with android app
      Serial.println(a);

      unsigned char bt_gait_idx = -1;

      switch (a) {
      case '0':
      case 'q':
        bt_gait_idx = 0;
        break; //stand
      case '5':
      case 'w':
        bt_gait_idx = 1;
        break; //forwards
      case '6':
      case 's':
        bt_gait_idx = 2;
        break; //reverse
      case '7':
      case 'a':
        bt_gait_idx = 3;
        break; //left
      case '8':
      case 'd':
        bt_gait_idx = 4;
        break; //right
      case 'e':
        bt_gait_idx = 5;
        break;
      default:
        bt_gait_idx = 0;
        break; //stand
      }

      Serial.print("b: ");
      Serial.println(bt_gait_idx);
      if (bt_gait_idx != -1 && a != '1') {
        gait_idx = bt_gait_idx;
        updateGait(gait_order[gait_idx]);
      }
    }
  }
}

void Robot::printServoPositions()
{
  for (int i = 0; i < legs_active; i++) {
    Serial.print(legs[i].id);
    Serial.print(": ");
    Serial.println(Dxl->getPosition(legs[i].id));
  }
}
