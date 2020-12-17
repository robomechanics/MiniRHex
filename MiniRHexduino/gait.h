#ifndef _GAIT_PARAMETERS_H
#define _GAIT_PARAMETERS_H

#define TOTAL_GAITS 7

#define STAND 0
#define WALK 1
#define REVERSE 2
#define LEFT 3
#define RIGHT 4
#define CLIMB 5
#define TEST 6  

struct Gait 
{
  int id;
  float kp;
  float kd;
  float theta_s[7];
  float theta_d[7];
  int leg_dir[7];
  int t_cc[7];
  float duty_f[7];
  float phases[7];
};

extern const Gait gait_order[TOTAL_GAITS];
extern const Gait climbing_gait;
extern const Gait stand_gait;
extern const Gait walk_gait;
extern const Gait reverse_gait;
extern const Gait right_gait;
extern const Gait left_gait;
extern const Gait test_gait;

#endif
