#ifndef _ROBOT_H
#define _ROBOT_H

#include "gait.h"
#include "leg.h"
#include <Dynamixel.h>

// Control Table //
#define MOVING_SPEED 32
#define PRESENT_POS 37
#define PRESENT_SPEED 39
#define PRESENT_VOLTAGE 45
#define LED 25

class Robot
{
    public:
        // Dynamixel Object
        Dynamixel *Dxl;

        unsigned char gait_idx;

        Robot(Dynamixel *dxl);
        ~Robot() {};
        void startup();
        unsigned short checkBattery();
        int incrementGait();
        int updateGait(Gait gait);
//        void jumpReady();
//        void jump();
        void update();
        void checkForBT();
        void printServoPositions();

    private:
        // Deadzone
        int dead_buffer = 40;

        // Legs setup //
        int legs_active;
        Leg legs[6];

        // Packet Setup //
        int packet_length;

        // Battery Check //
        unsigned char low_battery = 1; // 1 = red, 3 = yellow, 2 = green
        unsigned char prev_low_battery = 0;
        float voltage;

        float kp_hold = 0.008;
        float kd_hold = 1.0;

        float pd_calc(float theta_act, float theta_des,
                      float v_act, float v_des,
                      float kp, float kd);
        void update_leg_params();
};

#endif
