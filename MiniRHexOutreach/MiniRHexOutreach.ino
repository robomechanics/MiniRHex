#include "robot.h"
#include "behavior.h"

// Dynamixel Setup //
#define DXL_BUS_SERIAL1 1  // Dynamixel on Serial1(USART1) <-OpenCM9.04
Dynamixel dxl(DXL_BUS_SERIAL1);

Robot minirhex(&dxl);

// ---------------- EDIT HERE ---------------- //

Behavior behaviors[] = {
//  { gait, duration(millisecs) }
    { START, 0 },
    { STAND, 1000 },
    { WALK, 30000 },
    { END, 0 }
};
int b_idx = 0;
int t_start = 0;

// ------------------------------------------- //

void setup() {
    minirhex.setup();
    pinMode(BOARD_LED_PIN, OUTPUT); // setup LED
}

int count = 0;
void loop() {
    if (behaviors[b_idx].gait == START) {
        t_start = millis();
        b_idx++;
    }
    else if (millis() - t_start >= behaviors[b_idx].duration) {
        if (behaviors[b_idx].gait != END) {
            b_idx++;
            minirhex.updateGait(all_gaits[behaviors[b_idx].gait]);
            t_start = millis();
        }
    }

    // increment time count
    count++;

    // Every 100 loop iterations, find max voltage supplied to each leg and compare with nominal
    if (count % 10 == 0) {
      SerialUSB.println(minirhex.checkBattery());
    }

    minirhex.update();
}
