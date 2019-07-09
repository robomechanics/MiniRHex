#include "robot.h"
#include "behavior.h"

// Dynamixel Setup //
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1) <-OpenCM9.04
Dynamixel dxl(DXL_BUS_SERIAL1);

Robot minirhex(&dxl);

Behavior behaviors[] = {
//  {gait, duration}
    {START, 0},
    {STAND, 1000},
    {WALK, 50000},
    {END, 0}
};
int b_idx = 0;
int t_start = 0;

// Button Setup //
int button_state;
int last_button_state = 0;

void handle_button_press() {
    button_state = digitalRead(BOARD_BUTTON_PIN);
    if (button_state > last_button_state) {
        digitalWrite(BOARD_LED_PIN, LOW); // turn led on
        // int new_gait_idx = minirhex.incrementGait(); // change to next gait
        // SerialUSB.println(new_gait_idx);
    }
    else if (button_state < last_button_state) {
        digitalWrite(BOARD_LED_PIN, HIGH); // turn led off
    }
    last_button_state = button_state;
}

void setup() {
    minirhex.setup();
    Serial2.begin(57600); // set up serial usb input
    pinMode(BOARD_BUTTON_PIN, INPUT_PULLDOWN); // setup user button
    pinMode(BOARD_LED_PIN, OUTPUT); // setup LED
}

int count = 0;
void loop() {
    // if (behaviors[b_idx].gait == START) {
    //     t_start = millis();
    //     b_idx++;
    // }
    // else if (millis() - t_start >= behaviors[b_idx].duration) {
    //     if (behaviors[b_idx].gait != END) {
    //         b_idx++;
    //         minirhex.updateGait(all_gaits[behaviors[b_idx].gait]);
    //         t_start = millis();
    //     }
    // }

    // increment time count
    count++;

    // Every 100 loop iterations, find max voltage supplied to each leg and compare with nominal
    if (count % 10 == 0) {
      SerialUSB.println(minirhex.checkBattery());
    }

    // button control
    handle_button_press();

    minirhex.update();
    minirhex.checkForBT();
}
