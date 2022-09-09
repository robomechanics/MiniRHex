#include "leg_info.h"
#include "control_parameters.h"
#include "desired_values.h"
#include "pd_control.h"
#include "gait_parameters.h"

#include <DynamixelShield.h>

DynamixelShield dxl;
using namespace ControlTableItem;

// Rewritable globals
float desired_vel;
float desired_theta;
float actual_vel;
float actual_theta;
float control_signal;
float actual_p;

// Legs setup
const int legs_active = 6;

// Battery status
bool flash;         // LED on or off
bool shutdown;      // Disable motor movement
int voltage;        // Current battery voltage
int voltage_check;  // Current motor voltage

void setup() {
  Serial.begin(57600);                             // set the Serial Monitor to match this baud rate
  dxl.begin(57600);                                // 57600 is the default baud rate for XL330 motors
  dxl.setPortProtocolVersion(2.0);                 // XL330 motors use protocol 2

  pinMode(LED_BUILTIN, OUTPUT);                    // setup LED
  int t_start = millis();
  for (int i = 1; i <= legs_active; i++) {         // legs stored at their index
    dxl.torqueOff(legs[i].id);
    dxl.setOperatingMode(legs[i].id, OP_VELOCITY); // change servo to wheel mode
    dxl.writeControlTableItem(RETURN_DELAY_TIME, legs[i].id, 0);
    dxl.torqueOn(legs[i].id);
    update_gait(i, initial_gait, t_start);         // set initial parameters, initial_gait in gait_parameters
  }
}

void jump_ready() {
  int t_start = millis();
  for (int i = 1; i <= legs_active; i++) {
    legs[i].desired_theta = 90;
    update_gait(i, STAND, t_start);
  }
  Serial.println("JUMP READY");
}

void jump() {

  int t_start = millis();
  while (millis() - t_start < 900) {
    Serial.println(t_start - millis());
    if (millis() - t_start > 0) {
      dxl.setGoalVelocity(legs[1].id, 100, UNIT_PERCENT);
      dxl.setGoalVelocity(legs[4].id, -100, UNIT_PERCENT);
    }
    if (millis() - t_start > 100) {
      dxl.setGoalVelocity(legs[2].id, 100, UNIT_PERCENT);
      dxl.setGoalVelocity(legs[5].id, -100, UNIT_PERCENT);
    }
    if (millis() - t_start > 190) {
      dxl.setGoalVelocity(legs[3].id, 100, UNIT_PERCENT);
      dxl.setGoalVelocity(legs[6].id, -100, UNIT_PERCENT);
    }
  }
  for (int i = 1; i <= legs_active; i++) {
    legs[i].desired_theta = 0;
    update_gait(i, STAND, t_start);
  }
}

int count = 0;
int t = 0;
void loop() {

  // loop counter
  count++;

  // Every 10 loop iterations, find max voltage supplied to each leg and compare with nominal
  if (count % 10 == 0) {
    voltage = 0;
    for (int i = 1; i <= legs_active; i++) {
      voltage_check = dxl.readControlTableItem(PRESENT_INPUT_VOLTAGE, legs[i].id);
      if (voltage_check > voltage) voltage = voltage_check;
    }
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.print(", Frequency: ");
    Serial.print(10000/(millis()-t));
    Serial.println("Hz");
    t = millis();

    bool update = false;
    if (voltage > 45) {
      if (flash) update = true;
      flash = false;            // off (safe voltage)
      shutdown = false;
    }
    else if (voltage > 40) {
      if (!flash) update = true;
      flash = true;             // on (low voltage)
      shutdown = false;
    }
    else {
      if (!flash) update = true;
      flash = true;             // shutdown motors (very low voltage)
      shutdown = true;
    }

    if (update) {
      for (int i = 1; i <= legs_active; i++) {
        if (flash) {
          dxl.ledOn(legs[i].id);
        } else {
          dxl.ledOff(legs[i].id);
        }
      }
    }
  }

  // teleop control
  if (Serial.available()) {
    char a = (char)(Serial.read());
    int gait = -1;
    switch (a) {
      case 'q': // stand
        gait = STAND;
        break;
      case 'w': // forwards
        gait = WALK;
        break;
      case 'a': // left
        gait = LEFT;
        break;
      case 's': // reverse
        gait = REVERSE;
        break;
      case 'd': // right
        gait = RIGHT;
        break;
      case 'e': // pronk
        gait = PRONK;
        break;
      case 'x': // prepare jump
        jump_ready();
        break;
      case 'j': // jump
        jump();
        break;
    }

    if (gait != -1) {
      int t_start = millis();
      for (int i = 1; i <= legs_active; i++) {
        update_gait(i, gait, t_start);
      }
    }
  }

  // primary for-loop
  for (int i = 1; i <= legs_active; i++) {
    actual_theta = dxl.getPresentPosition(legs[i].id, UNIT_DEGREE); // degrees
    actual_vel = dxl.getPresentVelocity(legs[i].id, UNIT_RPM) * .06; // convert to deg/ms
    if (!legs[i].deadzone) {
      if (legs[i].gait == STAND) { // standing or sitting
        if (legs[i].right_side) {
          desired_theta = -legs[i].desired_theta;
        }
        else {
          desired_theta = legs[i].desired_theta;
        }
        actual_theta = actual_theta - legs[i].zero; // zero out leg thetas, accounts for small servo irregularities
        control_signal = pd_controller(actual_theta, desired_theta, actual_vel, 0, kp_hold, kd_hold);
      } else { // walking, turning
        // compute absolute desired values (theta and velocity) from clock time
        vals v = get_desired_vals(millis(), legs[i]);
        // translate theta and v to relative (left and right)
        if (legs[i].right_side) {
          desired_vel = -v.global_velocity; // relative
          desired_theta = -v.global_theta; // relative
        }
        else { // left side, relative is same as global
          desired_vel = v.global_velocity;
          desired_theta = v.global_theta;
        }
        actual_theta = actual_theta - legs[i].zero;

        control_signal = pd_controller(actual_theta, desired_theta, actual_vel, desired_vel, legs[i].kp, legs[i].kd);
      }
      int new_vel = actual_vel + control_signal;
      if (shutdown) {
        dxl.setGoalVelocity(legs[i].id, 0, UNIT_RPM);
      } else {
        dxl.setGoalVelocity(legs[i].id, new_vel / .06, UNIT_RPM);
      }
    }
  }
}