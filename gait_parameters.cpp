#include "gait_parameters.h"
#include "leg_info.h"

int active_mini = 2; //Mini 1 vs Mini 2
int initial_gait = STAND;

int walk_period = (active_mini == 2) ? 720:1500;
float walk_dutyf = (active_mini == 2) ? 0.42:0.75;
int walk_sweep = (active_mini == 2) ? 40:50;
int walk_down = (active_mini == 2) ? 20:5;

int pronk_period = 220;
float pronk_dutyf = 0.7;
int pronk_sweep = 60;

float kp_walk = .03; //.02 
float kd_walk = 1.0;

float kp_pronk = .03; //.1
float kd_pronk = 1.0; //1.5

Gait walk_gait = {{walk_sweep, walk_sweep, walk_sweep, walk_sweep, walk_sweep, walk_sweep, walk_sweep}, {0, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down}, {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period}, {walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf}, {0, 0.5, 0, 0.5, 0, 0.5, 0}, kp_walk, kd_walk};

Gait pronk_gait = {{pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep}, {0, -45, -55, -75, -45, -55, -75}, {pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period}, {pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf}, {0, 0, 0, 0, 0, 0, 0}, kp_pronk, kd_pronk};

