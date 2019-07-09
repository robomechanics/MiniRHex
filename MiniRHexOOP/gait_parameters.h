#ifndef _GAIT_PARAMETERS_H
#define _GAIT_PARAMETERS_H

#define TOTAL_GAITS 6

struct Gait {
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

#define STAND 0
#define WALK 1
#define REVERSE 2
#define LEFT 3
#define RIGHT 4
#define PRONK 5

extern Gait all_gaits[TOTAL_GAITS];
extern Gait stand_gait;
extern Gait walk_gait;
extern Gait reverse_gait;
extern Gait right_gait;
extern Gait left_gait;
extern Gait pronk_gait;

#endif
