#ifndef leg_info
#define leg_info

#include <math.h>

typedef struct leg_info_header leg;

struct leg_info_header{
  int id;
  float desired_theta; //only utilized in position control mode
  int forwards[5]; //changeable, direction of rotation in current gait
  int gait; //current gait
  float zero;
  bool right_side; //if right side we must convert absolute velocity and theta to relative velocity theta
  bool deadzone; //true if leg is currently in deadzone
  bool dead_from_neg;

  //Needs updated with each gait change
  
  float theta_slow;
  float theta_down;
  int t_c;
  float duty_factor;
  float phase;
  int startMillis;
  float kp;
  float kd;

  //computed from above in internal params
  
  float recovery_speed;
  float ground_speed;
  float thetas[5]; //0 through 4
  float ts[5]; //0 through 4


};

void update_gait(int leg_index, int gait, int startMillis);
void update_gait_internal_params(leg& l, int startTime);

extern leg legs[7];
extern int num_gaits;
extern const int STAND;
extern const int WALK;
extern const int LEFT;
extern const int REVERSE;
extern const int RIGHT;
extern const int PRONK;


#endif
