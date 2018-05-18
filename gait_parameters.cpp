#include "gait_parameters.h"
#include "leg_info.h"

int active_mini = 2; //Mini 1 vs Mini 2
int initial_gait = WALK;

int walk_period = 720; //720
float walk_dutyf = 0.42; //0.42
int walk_sweep = 40; //40
int walk_down = 20; //20


/* brick carrying
int walk_period = 1500; //720
float walk_dutyf = 0.75; //0.42
int walk_sweep = 50; //40
int walk_down = 5; //20
*/

int pronk_period = 400;
float pronk_dutyf = 0.7;
int pronk_sweep = 40;

float kp_walk = .03; //.02 
float kd_walk = 1.0;

float kp_pronk = .08; 
float kd_pronk = 1.5;

Gait walk_gait = {{walk_sweep, walk_sweep, walk_sweep, walk_sweep, walk_sweep, walk_sweep, walk_sweep}, {0, walk_down, walk_down, walk_down, walk_down, walk_down, walk_down}, {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period, walk_period}, {walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf, walk_dutyf}, {0, 0.5, 0, 0.5, 0, 0.5, 0}, kp_walk, kd_walk};

Gait pronk_gait = {{pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep, pronk_sweep}, {0, -50, -58, -66, -50, -58, -66}, {pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period, pronk_period}, {pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf, pronk_dutyf}, {0, 0, 0, 0, 0, 0, 0}, kp_pronk, kd_pronk};

