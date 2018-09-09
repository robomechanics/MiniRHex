#include "leg_info.h"
#include "control_parameters.h"
#include "desired_values.h"
#include "conversions.h"
#include "pd_control.h"
#include "gait_parameters.h"
#include <string.h>
#include <stdlib.h>

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

//TODO: move to bluetooth .h file
//For bluetooth Connection
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integerFromPC = 0;
float floatFromPC = 0.0;

//variables for parsed data
int dutyFactor_new;
int period_new;
int thetaDown_new;
int thetaSlow_new;
int kp_new;
int kd_new;
int turnMod_new; //turn command for steering miniRHex
int mode_new; //controls which gait miniRHex is using

int count = 0;

boolean newData = false;
//-----end bluetooth

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


// Serial parse for bluetooth connection
void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    
    while (Serial2.available() > 0 && newData == false) {
        rc = Serial2.read();
        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }
        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

// //============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    mode_new = atoi(strtokIndx); // copy it to messageFromPC
 
    strtokIndx = strtok(NULL, ",");
    turnMod_new = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    dutyFactor_new = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    period_new = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    thetaDown_new = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    thetaSlow_new = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    kp_new = atoi(strtokIndx);

    strtokIndx = strtok(NULL, ",");
    kd_new = atoi(strtokIndx);

}

void showParsedData() {
    SerialUSB.println("Mode ");
    SerialUSB.println(mode_new);
    SerialUSB.println("TurnMode ");
    SerialUSB.println(turnMod_new);
    SerialUSB.println("kp ");
    SerialUSB.println(kp_new);
}

void checkBatteryStatus() {
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
    //SerialUSB.println(voltage);

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
    //SerialUSB.println("Should switch led color here");
    for (int i = 1; i <= legs_active; i++){
      Dxl.writeByte(legs[i].id, LED, low_battery);
    }
  }
}



void loop(){

  checkBatteryStatus();
  
  // Check bluetooth connection for new data
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
        // this temporary copy is necessary to protect the original data
        //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    //showParsedData(); //prints values to usb serial
    newData = false;

    // TODO: make this a param or phase type in gait params file
    float phases[7] = {0, 0.5, 0, 0.5, 0, 0.5, 0};

    if (mode_new != -1){
    int t_start = millis(); 
      for (int i = 1; i <= legs_active; i++){
        update_gait(i, mode_new, t_start, dutyFactor_new, period_new, thetaDown_new, thetaSlow_new, kp_new, kd_new, phases[i]);
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
        vals v = get_desired_vals(millis(), legs[i], turnMod_new);
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

