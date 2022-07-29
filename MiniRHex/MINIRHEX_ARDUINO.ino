/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB
#else
  #define DEBUG_SERIAL Serial
#endif


const float DXL_PROTOCOL_VERSION = 2.0;
const uint8_t ID_AMOUNT = 6;
const uint8_t ID_LIST[ID_AMOUNT] = {1, 2, 3, 4, 5, 6};
//const uint8_t ID_LIST[ID_AMOUNT] = {1, 2};
int POS = 0;
uint8_t i;


DynamixelShield dxl;

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  
  // put your setup code here, to run once:
  
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);

  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(57600);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  
  // Get DYNAMIXEL information


 /*
  for(i = 0; i < ID_AMOUNT; i++) {
    if (i%2 == 0){
      dxl.ping(ID_LIST[i]);
      dxl.torqueOff(ID_LIST[i]);
      dxl.setOperatingMode(ID_LIST[i], OP_POSITION);
      dxl.torqueOn(ID_LIST[i]);
      dxl.setGoalPosition(ID_LIST[i], 0, UNIT_DEGREE);
    }
    else{
      dxl.ping(ID_LIST[i]);
      dxl.torqueOff(ID_LIST[i]);
      dxl.setOperatingMode(ID_LIST[i], OP_POSITION);
      dxl.torqueOn(ID_LIST[i]);
      dxl.setGoalPosition(ID_LIST[i], 180, UNIT_DEGREE);
    }
  }
  */ 

  for(i = 0; i < ID_AMOUNT; i++) {
      dxl.ping(ID_LIST[i]);
      dxl.torqueOff(ID_LIST[i]);
      dxl.setOperatingMode(ID_LIST[i], OP_POSITION);
      dxl.torqueOn(ID_LIST[i]);
      dxl.setGoalPosition(ID_LIST[i], 0, UNIT_DEGREE);
    }
    
  delay(5000);
  
  for(i = 0; i < ID_AMOUNT; i++) {
    dxl.torqueOff(ID_LIST[i]);
    dxl.setOperatingMode(ID_LIST[i], OP_VELOCITY);
    dxl.torqueOn(ID_LIST[i]);
    DEBUG_SERIAL.println(dxl.getPresentPosition(ID_LIST[i], UNIT_DEGREE));
  }
  
  delay(5000);
  
  


  /*for(i = 0; i < ID_AMOUNT; i++) {
    dxl.torqueOff(ID_LIST[i]);
    dxl.setOperatingMode(ID_LIST[i], OP_VELOCITY);
    dxl.torqueOn(ID_LIST[i]);
    dxl.setGoalVelocity(ID_LIST[i], 10, UNIT_RPM);
    if (i%2 == 0){
      DEBUG_SERIAL.println(dxl.readControlTableItem(PRESENT_SPEED, DXL_ID));
    }
  } */

/*tuple getPos(int LOWER_BOUND, int UPPER_BOUND){
  return (UPPER_BOUND_2, LOWER_BOUND_2)
}
*/

}



void loop() {
  
//GET POSITIONS 
int POS_1 = dxl.getPresentPosition(ID_LIST[0], UNIT_DEGREE);
int POS_2 = dxl.getPresentPosition(ID_LIST[1], UNIT_DEGREE);
int POS_GROUP_1 = POS_1%360;
int POS_GROUP_2 = POS_2%360;
int SLOW_VEL = 10;
int FAST_VEL = 50;
int LOWER_BOUND1 = 90;
int UPPER_BOUND1 = 135;
int LOWER_BOUND2 = (LOWER_BOUND1);
int UPPER_BOUND2 = (UPPER_BOUND1);

for(i = 0; i < ID_AMOUNT; i++) {
   if (i%2 == 0){
    if (LOWER_BOUND1 < UPPER_BOUND1){
      if (i > 2 && i <= ID_AMOUNT ){
        if (POS_GROUP_1 > LOWER_BOUND1 && POS_GROUP_1 < UPPER_BOUND1 ){
          dxl.setGoalVelocity(ID_LIST[i], -SLOW_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], -FAST_VEL, UNIT_RPM);
        }
      }
      else {
        if (POS_GROUP_1  > LOWER_BOUND1 && POS_GROUP_1 < UPPER_BOUND1 ){
          dxl.setGoalVelocity(ID_LIST[i], SLOW_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], FAST_VEL, UNIT_RPM);
        } 
      }
    }
    else{
      if (i > 2 && i <= ID_AMOUNT ){
        if (POS_GROUP_1 < LOWER_BOUND1 && POS_GROUP_1 > UPPER_BOUND1 ){
          dxl.setGoalVelocity(ID_LIST[i], -FAST_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], -SLOW_VEL, UNIT_RPM);
        }
      }
      else {
        if (POS_GROUP_1 < LOWER_BOUND1 && POS_GROUP_1 > UPPER_BOUND1 ){
          dxl.setGoalVelocity(ID_LIST[i], FAST_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], SLOW_VEL, UNIT_RPM);
        } 
      }
    }
  }
  else { /*START*/
    if (LOWER_BOUND2 < UPPER_BOUND2){
      if (i > 2 && i <= ID_AMOUNT ){
        if (POS_GROUP_2 > LOWER_BOUND2 && POS_GROUP_2 < UPPER_BOUND2 ){
          dxl.setGoalVelocity(ID_LIST[i], -SLOW_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], -FAST_VEL, UNIT_RPM);
        }
      }
      else {
        if (POS_GROUP_2  > LOWER_BOUND2 && POS_GROUP_2 < UPPER_BOUND2 ){
          dxl.setGoalVelocity(ID_LIST[i], SLOW_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], FAST_VEL, UNIT_RPM);
        } 
      }
    }
    else{
      if (i > 2 && i <= ID_AMOUNT ){
        if (POS_GROUP_2 < LOWER_BOUND2 && POS_GROUP_2 > UPPER_BOUND2 ){
          dxl.setGoalVelocity(ID_LIST[i], -FAST_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], -SLOW_VEL, UNIT_RPM);
        }
      }
      else {
        if (POS_GROUP_2  < LOWER_BOUND2 && POS_GROUP_2 > UPPER_BOUND2 ){
          dxl.setGoalVelocity(ID_LIST[i], FAST_VEL, UNIT_RPM);
        } 
        else {
          dxl.setGoalVelocity(ID_LIST[i], SLOW_VEL, UNIT_RPM);
        } 
      }
    }
  }
}
}
