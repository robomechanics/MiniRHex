#include "robot.h"
#include <Dynamixel.h>

// Dynamixel Setup //
#define DXL_BUS_SERIAL1 1  // Dynamixel on Serial1(USART1) <-OpenCM9.04
Dynamixel Dxl(DXL_BUS_SERIAL1);

Robot MiniRHex(&Dxl);

// Button Setup //
unsigned char button_state;
unsigned char last_button_state = 0;
unsigned long button_t = millis();

void handle_button_press() {
  button_state = digitalRead(BOARD_BUTTON_PIN);
  if (button_state > last_button_state) {
      button_t = millis();
      digitalWrite(BOARD_LED_PIN, LOW); // turn led on
      int new_gait_idx = MiniRHex.incrementGait(); // change to next gait
  }
  else if (button_state < last_button_state) {
    digitalWrite(BOARD_LED_PIN, HIGH); // turn led off
  }
  last_button_state = button_state;
}

void setup() {
  MiniRHex.startup();
  Serial2.begin(57600);
  pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN); // setup user button
  pinMode(BOARD_LED_PIN, OUTPUT); // setup LED
}

unsigned long t = millis();
void loop() {
  // Every second, find max voltage supplied to each leg and compare with nominal // 
  if (millis() - t > 1000) {
    t = millis();
    MiniRHex.checkBattery();
  }
  // button control //
  handle_button_press();
  
  MiniRHex.update();
  MiniRHex.checkForBT();
}
