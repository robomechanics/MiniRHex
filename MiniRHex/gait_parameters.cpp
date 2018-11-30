#include "gait_parameters.h"
#include "leg_info.h"

int active_mini = 1; //1 = black, 2 = orange, 3 = blue, 4 = purple
int initial_gait = STAND;

float kp_walk = .03; //.02 
float kd_walk = 1.0;
int walk_period = 2000;//720;

//----------EDIT HERE----------------//

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
float leg1_dutyf = .42;
int leg1_sweep = 40;
int leg1_down = 20;
float leg1_phase = 0.5;
 
//Leg 2 (Left Middle) Parameters:
float leg2_dutyf = .42;
int leg2_sweep = 40;
int leg2_down = 20;
float leg2_phase = 0;

//Leg 3 (Left Rear) Parameters:
float leg3_dutyf = .42;
int leg3_sweep = 40;
int leg3_down = 20;
float leg3_phase = 0.5;

//Leg 4 (Right Front) Parameters:
float leg4_dutyf = .42;
int leg4_sweep = 40;
int leg4_down = 20;
float leg4_phase = 0;

//Leg 5 (Right Middle) Parameters:
float leg5_dutyf = .42;
int leg5_sweep = 40;
int leg5_down = 20;
float leg5_phase = 0.5;

//Leg 6 (Right Rear) Parameters
float leg6_dutyf = .42;
int leg6_sweep = 40;
int leg6_down = 20;
float leg6_phase = 0;

//-----------------------------------//




Gait walk_gait = {{0, leg1_sweep, leg2_sweep, leg3_sweep, leg4_sweep, leg5_sweep, leg6_sweep}, {0, leg1_down, leg2_down, leg3_down, leg4_down, leg5_down, leg6_down}, {0, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period}, {0, leg1_dutyf, leg2_dutyf, leg3_dutyf, leg4_dutyf, leg5_dutyf, leg6_dutyf}, {0, leg1_phase, leg2_phase, leg3_phase, leg4_phase, leg5_phase, leg6_phase}, kp_walk, kd_walk};

int pronk_period = 220;
float pronk_dutyf = 0.7;
int pronk_sweep = 60;
float kp_pronk = .03; //.1
float kd_pronk = 1.0; //1.5
Gait pronk_gait = {{pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep}, {0, -45, -55, -75, -45, -55, -75}, {pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period}, {pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf}, {0, 0, 0, 0, 0, 0, 0}, kp_pronk, kd_pronk};

