#ifndef pd_control
#define pd_control

float pd_controller(float theta_act, float theta_des, float v_act, float v_des, float kp, float kd);

extern float kp_hold;
extern float kd_hold;

#endif
