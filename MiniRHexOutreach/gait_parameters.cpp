#include "gait_parameters.h"
#include "leg_info.h"

float kp_walk = 0;
float kd_walk = 0;
int walk_period = 0;

// ---------------- EDIT HERE ---------------- //

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
float leg1_dutyf = 0;
int leg1_sweep = 0;
int leg1_down = 0;
float leg1_phase = 0;

//Leg 2 (Left Middle) Parameters:
float leg2_dutyf = 0;
int leg2_sweep = 0;
int leg2_down = 0;
float leg2_phase = 0;

//Leg 3 (Left Rear) Parameters:
float leg3_dutyf = 0;
int leg3_sweep = 0;
int leg3_down = 0;
float leg3_phase = 0;

//Leg 4 (Right Front) Parameters:
float leg4_dutyf = 0;
int leg4_sweep = 0;
int leg4_down = 0;
float leg4_phase = 0;

//Leg 5 (Right Middle) Parameters:
float leg5_dutyf = 0;
int leg5_sweep = 0;
int leg5_down = 0;
float leg5_phase = 0;

//Leg 6 (Right Rear) Parameters
float leg6_dutyf = 0;
int leg6_sweep = 0;
int leg6_down = 0;
float leg6_phase = 0;

// ------------------------------------------- //

Gait stand_gait {
    STAND, // Don't change; gait index
    kp_walk, kd_walk, // pd gains
    {0, leg1_sweep, leg2_sweep, leg3_sweep, leg4_sweep, leg5_sweep, leg6_sweep}, // Angle width of "slow phase" in degrees
    {0, leg1_down, leg2_down, leg3_down, leg4_down, leg5_down, leg6_down}, // Center angle of the "slow phase" in degrees
    {0, 1, 1, 1, 1, 1, 1}, // Don't change; leg directions
    {0, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period}, // Gait period
    {0, leg1_dutyf, leg2_dutyf, leg3_dutyf, leg4_dutyf, leg5_dutyf, leg6_dutyf}, // Percentage of time legs are in a standing position
    {0, leg1_phase, leg2_phase, leg3_phase, leg4_phase, leg5_phase, leg6_phase} // Relative timing of legs
};

Gait walk_gait {
    WALK,
    kp_walk, kd_walk,
    {0, leg1_sweep, leg2_sweep, leg3_sweep, leg4_sweep, leg5_sweep, leg6_sweep},
    {0, leg1_down, leg2_down, leg3_down, leg4_down, leg5_down, leg6_down},
    {0, 1, 1, 1, 1, 1, 1},
    {0, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {0, leg1_dutyf, leg2_dutyf, leg3_dutyf, leg4_dutyf, leg5_dutyf, leg6_dutyf},
    {0, leg1_phase, leg2_phase, leg3_phase, leg4_phase, leg5_phase, leg6_phase}
};

Gait reverse_gait {
    REVERSE,
    kp_walk, kd_walk,
    {0, leg1_sweep, leg2_sweep, leg3_sweep, leg4_sweep, leg5_sweep, leg6_sweep},
    {0, leg1_down, leg2_down, leg3_down, leg4_down, leg5_down, leg6_down},
    {0, -1, -1, -1, -1, -1, -1},
    {0, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {0, leg1_dutyf, leg2_dutyf, leg3_dutyf, leg4_dutyf, leg5_dutyf, leg6_dutyf},
    {0, leg1_phase, leg2_phase, leg3_phase, leg4_phase, leg5_phase, leg6_phase}
};

Gait left_gait {
    LEFT,
    kp_walk, kd_walk,
    {0, leg1_sweep, leg2_sweep, leg3_sweep, leg4_sweep, leg5_sweep, leg6_sweep},
    {0, leg1_down, leg2_down, leg3_down, leg4_down, leg5_down, leg6_down},
    {0, -1, -1, -1, 1, 1, 1},
    {0, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {0, leg1_dutyf, leg2_dutyf, leg3_dutyf, leg4_dutyf, leg5_dutyf, leg6_dutyf},
    {0, leg1_phase, leg2_phase, leg3_phase, leg4_phase, leg5_phase, leg6_phase}
};

Gait right_gait {
    RIGHT,
    kp_walk, kd_walk,
    {0, leg1_sweep, leg2_sweep, leg3_sweep, leg4_sweep, leg5_sweep, leg6_sweep},
    {0, leg1_down, leg2_down, leg3_down, leg4_down, leg5_down, leg6_down},
    {0, 1, 1, 1, -1, -1, -1},
    {0, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {0, leg1_dutyf, leg2_dutyf, leg3_dutyf, leg4_dutyf, leg5_dutyf, leg6_dutyf},
    {0, leg1_phase, leg2_phase, leg3_phase, leg4_phase, leg5_phase, leg6_phase}
};

int pronk_period = 0;
float pronk_dutyf = 0;
int pronk_sweep = 0;
float kp_pronk = 0;
float kd_pronk = 0;

Gait pronk_gait {
    PRONK,
    kp_pronk, kd_pronk,
    {pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep},
    {0, -45, -55, -75, -45, -55, -75},
    {0, 1, 1, 1, 1, 1, 1},
    {pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period},
    {pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf},
    {0, 0, 0, 0, 0, 0, 0}
};

Gait all_gaits[TOTAL_GAITS] = {stand_gait, walk_gait, reverse_gait, left_gait, right_gait, pronk_gait};
