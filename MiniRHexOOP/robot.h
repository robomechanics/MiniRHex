#ifndef _ROBOT_H
#define _ROBOT_H

#include "gait_parameters.h"
#include "leg_info.h"
#include "Dynamixel.h"

#define DXL_BUS_SERIAL1 1

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

        // Servo zeros
        float *zeros;

        int gait_idx;

        // Rewritable globals
        float desired_vel;
        float desired_theta;
        float actual_vel;
        float actual_theta;
        float control_signal;
        float actual_p;

        Robot(Dynamixel *dxl);
        Robot(float set_zeros[7], Dynamixel *dxl);
        ~Robot() {};
        void setup();
        int checkBattery();
        int incrementGait();
        int updateGait(Gait gait);
        void jumpReady();
        void jump();
        void update();
        void checkForBT();
        void printServoPositions();

    private:
        //Deadzone
        int dead_buffer;

        // Legs setup //
        int legs_active;
        Leg legs[7];

        // Packet Setup //
        int packet_length;
        // word *packet;

        int index;

        // Battery Check //
        int low_battery; // 1 = red, 3 = yellow, 2 = green
        int prev_low_battery;
        int voltage;
        int voltage_check;

        float kp_hold;
        float kd_hold;

        float pd_calc(float theta_act, float theta_des,
                      float v_act, float v_des,
                      float kp, float kd);
};

#endif
