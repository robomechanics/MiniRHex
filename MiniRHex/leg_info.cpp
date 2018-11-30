#include "leg_info.h"
#include "control_parameters.h"
#include "gait_parameters.h"
#include <fstream>

const int STAND = 0;
const int WALK = 1;
const int LEFT = 2;
const int REVERSE = 3;
const int RIGHT = 4;
const int PRONK = 5;


void update_gait(int leg_index, int gait, int startMillis){
  Gait new_gait = (gait == PRONK) ? pronk_gait: walk_gait;
  printf("Gait %d\n", new_gait.t_cc[leg_index]);
  legs[leg_index].gait = gait;
  legs[leg_index].theta_slow = new_gait.theta_s[leg_index];
  legs[leg_index].theta_down = new_gait.theta_d[leg_index];
  legs[leg_index].t_c = new_gait.t_cc[leg_index];
  legs[leg_index].duty_factor = new_gait.duty_f[leg_index];
  legs[leg_index].phase = new_gait.phases[leg_index];
  legs[leg_index].kp = new_gait.kp;
  legs[leg_index].kd = new_gait.kd;
  update_gait_internal_params(legs[leg_index], startMillis);
}

void update_gait_internal_params(leg& l, int startTime){
  float ground_speed;
  float recovery_speed;
  int t_s = round(l.t_c * l.duty_factor);

  if (l.gait == PRONK){
    ground_speed = l.theta_slow / t_s;
    recovery_speed = -l.theta_slow / (l.t_c - t_s);

    l.thetas[0] = l.theta_down;
    l.ts[0] = 0;

    l.thetas[1] = l.theta_down - l.theta_slow/2;
    l.ts[1] = l.ts[0] + (l.thetas[1] - l.thetas[0]) / recovery_speed;

    l.thetas[2] = l.theta_down;
    l.ts[2] = l.ts[1] + (l.thetas[2] - l.thetas[1]) / ground_speed;

    l.thetas[3] = l.theta_down + l.theta_slow/2;
    l.ts[3] = l.ts[2] + (l.thetas[3] - l.thetas[2]) / ground_speed;

    l.thetas[4] = l.theta_down;
    l.ts[4] = l.t_c;

  }
  else{ //all walking gaits (and standing technically)
    
    ground_speed = l.theta_slow / t_s;
    recovery_speed = (theta_circle - l.theta_slow) / (l.t_c - t_s);

    l.thetas[0] = l.theta_down - theta_circle + theta_up;
    l.ts[0] = 0;

    l.thetas[1] = l.theta_down - l.theta_slow/2;
    l.ts[1] = l.ts[0] + (l.thetas[1] - l.thetas[0]) / recovery_speed;

    l.thetas[2] = l.theta_down;
    l.ts[2] = l.ts[1] + (l.thetas[2] - l.thetas[1]) / ground_speed;

    l.thetas[3] = l.theta_down + l.theta_slow/2;
    l.ts[3] = l.ts[2] + (l.thetas[3] - l.thetas[2]) / ground_speed;

    l.thetas[4] = l.theta_down + theta_up;
    l.ts[4] = l.t_c;

  }
  l.startMillis = startTime;
  l.ground_speed = ground_speed;
  l.recovery_speed = recovery_speed;

}

//stand forward left back right pronk
int num_gaits = 6;

/*
MODIFY THESE ARRAYS TO CONFIGURE ROBOT
(mini1 and mini2 are our two prototypes, ignore mini2 array if you're only using one robot)
be sure to set active_mini to 1 in gait_parameters.cpp
*/
//float mini1Zeros[6] = {-3.22, -6.15, -7.03, -17.29, 0, 4.39}; //miniRHex Black
float mini1Zeros[6] = {0.29, 1.46, 0.29, -2.34, 1.17, 0.29}; //miniRHex Orange
//float mini1Zeros[6] = {0, 1.17, -0.88, 0.29, -1.46, -0.29}; // miniRHex Blue
//float mini1Zeros[6] = {0.59, -19.04, -1.76, -17.29,-0.59,-15.53}; //miniRHex Purple

float mini2Zeros[6] = {-0.59, -17.87, -1.76, 0.88, -5.27, -1.76};
int IDS[6] = {1, 2, 3, 4, 5, 6};

///////////////////////

float *zeros = (active_mini == 1) ? mini1Zeros : mini2Zeros;

leg fake_leg0 = {0, 0, {1,  1,  1,  1, 1},    0,   0,       false, false, false}; //this leg is a spacer in the array, only used to make each leg's index be equal to its number
leg leg1 =      {IDS[0], 0, {1, -1, -1,  1, 1},    0, zeros[0],  false, false, false};
leg leg2 =      {IDS[1], 0, {1, -1, -1,  1, 1},    0, zeros[1],  false, false, false};
leg leg3 =      {IDS[2], 0, {1, -1, -1,  1, 1},    0, zeros[2],  false, false, false};
leg leg4 =      {IDS[3], 0, {1,  1, -1, -1, 1},    0, zeros[3],  true,  false, false};
leg leg5 =      {IDS[4], 0, {1,  1, -1, -1, 1},    0, zeros[4],  true,  false, false};
leg leg6 =      {IDS[5], 0, {1,  1, -1, -1, 1},    0, zeros[5],  true,  false, false};
leg legs[] = {fake_leg0, leg1, leg2, leg3, leg4, leg5, leg6};

