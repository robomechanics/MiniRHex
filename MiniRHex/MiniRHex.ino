#include "leg_info.h"
#include "control_parameters.h"
#include "desired_values.h"
#include "conversions.h"
#include "pd_control.h"
#include "gait_parameters.h"

// Dynamixel Setup //
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
Dynamixel Dxl(DXL_BUS_SERIAL1);

// Control Table //
#define MOVING_SPEED 32
#define PRESENT_POS 37
#define PRESENT_SPEED 39
#define PRESENT_VOLTAGE 45
#define LED 25

//Rewritable globals
float desired_vel;
float desired_theta;
float actual_vel;
float actual_theta;
float control_signal;
float actual_p;


//Deadzone
int dead_buffer = 40;

// Legs setup //
const int legs_active = 6;

// Packet Setup //
const int packet_length =  2 * legs_active;
word packet[packet_length]; 

// Button Setup //
int button_state;
int last_button_state = 0;

// Battery Check //
int low_battery = 1; // 1 = red, 3 = yellow, 2 = green
int prev_low_battery = 0;
int voltage;
int voltage_check;

void setup(){
  Dxl.begin(3); //baudrate set to 1 Mbps (max)
  Serial2.begin(57600); //set up serial usb input
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN); //setup user button
  pinMode(BOARD_LED_PIN, OUTPUT); //setup LED
  int t_start = millis();
  for (int i = 1; i <= legs_active; i++){ //legs stored at their index
    Dxl.wheelMode(legs[i].id); //change servo to wheel mode
    update_gait(i, initial_gait, t_start); //set initial parameters, initial_gait in gait_parameters
  }
}

void user_button_pressed(){
  
  digitalWrite(BOARD_LED_PIN, LOW); //turn led on
  //compute new gait
  int new_gait = (legs[1].gait + 1) % num_gaits;
  int t_start = millis();
  for(int i = 1; i <= legs_active; i++){
    update_gait(i, new_gait, t_start);
  }
  
}

void user_button_released(){
  digitalWrite(BOARD_LED_PIN, HIGH);
}

void jump_ready(){
  int t_start = millis(); 
  for (int i = 1; i <= legs_active; i++){
    legs[i].desired_theta = 90;
    update_gait(i, STAND, t_start);
  }
  SerialUSB.println("JUMP READY");
}

void jump(){

  int t_start = millis();
  while (millis() - t_start < 900){
    SerialUSB.println(t_start - millis());
    if (millis() - t_start > 0){
      Dxl.writeWord(1, MOVING_SPEED, 1023);
      Dxl.writeWord(4, MOVING_SPEED, 2047);
    }
    if (millis() - t_start > 100){
      Dxl.writeWord(2, MOVING_SPEED, 1023);
      Dxl.writeWord(5, MOVING_SPEED, 2047);
    }
    if (millis() - t_start > 190){
      Dxl.writeWord(3, MOVING_SPEED, 1023);
      Dxl.writeWord(6, MOVING_SPEED, 2047);
    }
  }
  for (int i = 1; i <= legs_active; i++){
    legs[i].desired_theta = 0;
    update_gait(i, STAND, t_start);
  }

}

int count = 0;
void loop(){

  //time count
  count++;
  
  prev_low_battery = low_battery;
  //Every 100 loop iterations, find max voltage supplied to each leg and compare with nominal
  if (count%10 == 0){
    voltage = 0;
    for (int i = 1; i <= legs_active; i++){
      voltage_check = Dxl.readByte(legs[1].id, PRESENT_VOLTAGE);
      if (voltage_check > voltage) voltage = voltage_check;
    }
    SerialUSB.println(voltage);

    if (voltage > 73){ //green
      low_battery = 2;
    }
    else if (voltage < 71){ //red
      low_battery = 1;
    }
    else{
      low_battery = 3; //yellow
    }
  }

  if (prev_low_battery != low_battery){
    SerialUSB.println("Should switch led color here");
    for (int i = 1; i <= legs_active; i++){
      Dxl.writeByte(legs[i].id, LED, low_battery);
    }
  }
  
  //bluetooth control
  if (Serial2.available()){ 
    char a = (char)(Serial2.read());
    int gait = -1;
    switch (a){
    case 'q': 
      gait = STAND; 
      break; //stand
    case 'w': 
      gait = WALK; 
      break; //forwards
    case 'a': 
      gait = LEFT; 
      break; //left
    case 's': 
      gait = REVERSE; 
      break; //reverse
    case 'd': 
      gait = RIGHT; 
      break; //right 
    case 'e':
      gait = PRONK;
      break;
    case 'x':
      jump_ready();
      break;
    case 'j':
      jump();
      break;
    }

    if (gait != -1){
      int t_start = millis(); 
      for (int i = 1; i <= legs_active; i++){
        update_gait(i, gait, t_start);
      }
    }
  }

  //button control
  button_state = digitalRead(BOARD_BUTTON_PIN);
  if (button_state > last_button_state) user_button_pressed();
  else if (button_state < last_button_state) user_button_released();
  last_button_state = button_state;


  //primary for-loop
  for(int i = 1; i <= legs_active; i++){
    packet[(i-1) * 2] = legs[i].id;
    actual_p = Dxl.readWord(legs[i].id, PRESENT_POS);
    actual_theta = P_to_Theta(actual_p); // converted to degrees, relative to leg
    actual_vel = dynV_to_V(Dxl.readWord(legs[i].id, PRESENT_SPEED)); // converted to degrees/ms, relative to leg
    if (!legs[i].deadzone){
      
      if (actual_p == 0 || actual_p == 1023){ //entering deadzone
        legs[i].deadzone = true;
        if (actual_p == 0) legs[i].dead_from_neg = true;
        else legs[i].dead_from_neg = false;
        continue;
      }

      if (legs[i].gait == STAND){ //standing or sitting
        if (legs[i].right_side){
          desired_theta = Theta_to_ThetaR(legs[i].desired_theta);
        }
        else{
          desired_theta = legs[i].desired_theta;
        }
        actual_theta = actual_theta - legs[i].zero; //zero out leg thetas, accounts for small servo irregularities
        control_signal = pd_controller(actual_theta, desired_theta, actual_vel, 0, kp_hold, kd_hold); 
      }
      else { //walking, turning
        //compute absolute desired values (theta and velocity) from clock time
        vals v = get_desired_vals(millis(), legs[i]);
        //translate theta and v to relative (left and right)
        if (legs[i].right_side){
          desired_vel = -v.global_velocity; //relative
          desired_theta = Theta_to_ThetaR(v.global_theta); // relative
        }
        else{ //left side, relative is same as global
          desired_vel = v.global_velocity;
          desired_theta = v.global_theta;
        }
        actual_theta = actual_theta - legs[i].zero;
        
        control_signal = pd_controller(actual_theta, desired_theta, actual_vel, desired_vel, legs[i].kp, legs[i].kd);  
      }


      int new_vel = V_to_dynV(actual_vel + control_signal);
      packet[(i-1) * 2 + 1] = new_vel;
    }

    else{ //deadzone
      if ((actual_p > 0) & (actual_p < dead_buffer) || (actual_p < 1023) & (actual_p > 1023 -dead_buffer)){ //exiting deadzone
        legs[i].deadzone = false;
      }
      float signed_recovery_speed = legs[i].dead_from_neg == true ? -legs[i].recovery_speed : legs[i].recovery_speed;
      packet[(i-1) * 2 + 1] = V_to_dynV(signed_recovery_speed);
    }
  }

  Dxl.syncWrite(MOVING_SPEED, 1, packet, packet_length); //simultaneously write to each of 6 servoes with updated commands
}



