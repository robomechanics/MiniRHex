#ifndef _LEG_INFO_H
#define _LEG_INFO_H

#include "gait.h"

class Leg
{
  public:
    unsigned char id;
    unsigned char idx;
    float desired_theta; // only utilized in position control mode
    Gait gait; // current gait
    float zero;
    bool right_side; // if right side we must convert absolute velocity and theta to relative velocity theta
    bool deadzone; // true if leg is currently in deadzone
    bool dead_from_neg;

    // Needs updated with each gait change
    float theta_slow;
    float theta_down;
    int t_c;
    float duty_factor;
    float phase;
    int startMillis;
    float kp;
    float kd;

    // Computed from above in internal params
    float recovery_speed;
    float ground_speed;
    float thetas[4]; // 0 through 4
    float ts[4]; // 0 through 4

    float global_theta;
    float global_velocity;

    int position;
    int velocity;

    Leg() {};
    Leg(unsigned char set_id, unsigned char set_idx, int pos, int vel,
        float set_desired_theta, Gait set_gait,
        float set_zero, bool set_right_side,
        bool set_deadzone, bool set_dead_from_neg);
    ~Leg() {};
    void updateGait(Gait new_gait, int startMillis);
    void getDesiredVals(int t);
    void getDesiredValsInternal(int t);

  private:
    void updateGaitInternalParams(int startTime);
};

#endif
