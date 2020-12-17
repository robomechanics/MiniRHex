#ifndef _GAIT_PARAMETERS_H
#define _GAIT_PARAMETERS_H

#define TOTAL_GAITS 5

#define STAND 0
#define WALK 1
#define REVERSE 2
#define LEFT 3
#define RIGHT 4

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
};

extern const Gait gait_order[TOTAL_GAITS];
extern const Gait stand_gait;
extern const Gait walk_gait;
extern const Gait reverse_gait;
extern const Gait right_gait;
extern const Gait left_gait;

#endif
