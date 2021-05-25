#ifndef _GAIT_PARAMETERS_H
#define _GAIT_PARAMETERS_H

#include "tgait.h" 

#define TOTAL_GAITS 2

#define STAND 0
#define WALK 1
#define REVERSE 2
#define LEFT 3
#define RIGHT 4
#define CLIMB 5
#define CLIMB1 6
#define CLIMB2 7
#define CLIMB3 8 
#define CLIMB4 9 
#define CLIMB5 10
#define CLIMB6 11
#define CLIMB7 12
#define CLIMB8 13
#define CLIMB9 14
#define CLIMB10 15
#define CLIMB11 16
#define CLIMB12 17

struct Gait 
{
  int id;
  float kp;
  float kd;
  float theta_s[6];
  float theta_d[6];
  int leg_dir[6];
  int t_cc[6];
  float duty_f[6];
  float phases[6];
  tGait tgait;
  
};

extern const Gait gait_order[TOTAL_GAITS];
extern const Gait stand_gait;
extern const Gait walk_gait;
extern const Gait reverse_gait;
extern const Gait right_gait;
extern const Gait left_gait;
extern const Gait climbing_gait; 

#endif
