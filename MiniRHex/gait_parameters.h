#ifndef gait_parameters
#define gait_parameters

typedef struct gait_container Gait;

struct gait_container{
  float theta_s[7];
  float theta_d[7];
  int t_cc[7];
  float duty_f[7];
  float phases[7];
  float kp;
  float kd;
};

extern int active_mini;
extern int initial_gait;
extern Gait walk_gait;
extern Gait pronk_gait;

#endif