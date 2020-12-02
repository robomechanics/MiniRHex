#include "gait.h"
#include "leg.h"

const float kp_walk = 0.03; // 0.02
const float kd_walk = 1.0;
const int walk_period = 2000; // 720;

/*
Explanation of parameters:

Duty Factor: Percentage of time the leg is in a standing position
(0 is always "fast", 1 is always "slow") (takes decimal values of 0-1)

Sweep: angle width of "slow phase" in degrees (takes integer values 0-360)

Down: center angle of the "slow phase" in degrees (takes integer values 0-360)

Phase: Determines the relative timing of the legs. Takes values from 0-1.
A phase of .5 will( have the leg at the opposite part of the cycle from a leg
with a phase of 0 ) (takes decimal values 0-1)
*/

//Leg 1 (Left Front) Parameters:
const float leg_dutyf = 0.42;
const float leg_sweep = 40.0;
const float leg_down = 20.0;
const float leg_phase1 = 0.50;
const float leg_phase2 = 0.0;



// -------------------------------------- //

const Gait stand_gait {
    STAND,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {1, 1, 1, 1, 1, 1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase1, leg_phase1, leg_phase1, leg_phase1, leg_phase1}
};

const Gait walk_gait {
    WALK,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {1, 1, 1, 1, 1, 1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2}
};

const Gait reverse_gait {
    REVERSE,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {-1, -1, -1, -1, -1, -1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2}
};

const Gait left_gait {
    LEFT,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {-1, -1, -1, 1, 1, 1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2}
};

const Gait right_gait {
    RIGHT,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {1, 1, 1, -1, -1, -1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2}
};


/*
Explanation of parameters:

Duty Factor: Percentage of time the leg is in a standing position
(0 is always "fast", 1 is always "slow") (takes decimal values of 0-1)

Sweep: angle width of "slow phase" in degrees (takes integer values 0-360)

Down: center angle of the "slow phase" in degrees (takes integer values 0-360)

Phase: Determines the relative timing of the legs. Takes values from 0-1.
A phase of .5 will( have the leg at the opposite part of the cycle from a leg
with a phase of 0 ) (takes decimal values 0-1)
*/

//Leg 1 (Left Front) Parameters for Climbing:
const float leg_dutyc = 0.75;
const float leg_sweepc = 75.0;
const float leg_downc = 20.0;
const float leg_phase1c = 0.50;
const float leg_phase2c = 0.0;
const float leg_phase3c = 0.25; 

const int walk_periodc = 2500; // 2000;



//Tail Parameters 
const float tail_dutyf = 0.42;
const float tail_sweep = 40.0;
const float tail_down = 20.0;
const float tail_phase1 = 0.50;
const float tail_phase2 = 0.0;


const Gait climbing_gait {
    WALK,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, tail_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down, tail_down},
    {-1, -1, -1, -1, -1, -1, -1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period, 0},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, tail_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2, tail_phase2}
};

const Gait test_gait {
    WALK,
    kp_walk, kd_walk,
    {leg_sweepc, leg_sweepc, leg_sweepc, leg_sweepc, leg_sweepc, leg_sweepc, tail_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down, tail_down},
    {-1, -1, -1, -1, -1, -1, -1},
    {walk_periodc, walk_periodc, walk_periodc, walk_periodc, walk_periodc, walk_periodc, 0},
    {leg_dutyc, leg_dutyc, leg_dutyc, leg_dutyc, leg_dutyc, leg_dutyc, tail_dutyf},
    {leg_phase1c, leg_phase3c, leg_phase2c, leg_phase1c, leg_phase3c, leg_phase2c, tail_phase2}
};

const Gait gait_order[TOTAL_GAITS] = {climbing_gait, test_gait, stand_gait, walk_gait, reverse_gait, left_gait, right_gait};
