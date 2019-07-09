#include <math.h>
#include <fstream>
#include "leg_info.h"
#include "gait_parameters.h"
#include "conversions.h"

Leg::Leg(int set_id,
    float set_desired_theta, Gait set_gait,
    float set_zero, bool set_right_side,
    bool set_deadzone, bool set_dead_from_neg)
{
    id = set_id;
    desired_theta = set_desired_theta;
    gait = set_gait;
    zero = set_zero;
    right_side = set_right_side;
    deadzone = set_deadzone;
    dead_from_neg = set_dead_from_neg;
    updateGait(stand_gait, 0);
}

void Leg::updateGait(Gait new_gait, int startMillis)
{
    // Gait new_gait = all_gaits[gait_idx];
    gait = new_gait;
    theta_slow = new_gait.theta_s[id];
    theta_down = new_gait.theta_d[id];
    t_c = new_gait.t_cc[id];
    duty_factor = new_gait.duty_f[id];
    phase = new_gait.phases[id];
    kp = new_gait.kp;
    kd = new_gait.kd;
    updateGaitInternalParams(startMillis);
}

void Leg::updateGaitInternalParams(int startTime)
{
    float ground_spd;
    float recovery_spd;
    int t_s = round(t_c * duty_factor);

    if (gait.id == 5) {
        ground_speed = theta_slow / t_s;
        recovery_spd = -theta_slow / (t_c - t_s);

        thetas[0] = theta_down;
        ts[0] = 0;

        thetas[1] = theta_down - theta_slow/2;
        ts[1] = ts[0] + (thetas[1] - thetas[0]) / recovery_spd;

        thetas[2] = theta_down;
        ts[2] = ts[1] + (thetas[2] - thetas[1]) / ground_spd;

        thetas[3] = theta_down + theta_slow/2;
        ts[3] = ts[2] + (thetas[3] - thetas[2]) / ground_spd;

        thetas[4] = theta_down;
        ts[4] = t_c;
    }
    else //all walking gaits (and standing technically)
    {
        ground_spd = theta_slow / t_s;
        recovery_spd = (theta_circle - theta_slow) / (t_c - t_s);

        thetas[0] = theta_down - theta_circle + theta_up;
        ts[0] = 0;

        thetas[1] = theta_down - theta_slow/2;
        ts[1] = ts[0] + (thetas[1] - thetas[0]) / recovery_spd;

        thetas[2] = theta_down;
        ts[2] = ts[1] + (thetas[2] - thetas[1]) / ground_spd;

        thetas[3] = theta_down + theta_slow/2;
        ts[3] = ts[2] + (thetas[3] - thetas[2]) / ground_spd;

        thetas[4] = theta_down + theta_up;
        ts[4] = t_c;
    }
    startMillis = startTime;
    ground_speed = ground_spd;
    recovery_speed = recovery_spd;
}

void Leg::setDesiredTheta(int new_pos) {
    desired_theta = new_pos;
}

void Leg::getDesiredVals(int t) { // handles phasing and start time, user provides get desired vals internal function
  int elapsed_time = t - startMillis;

  t = fmodf(elapsed_time + phase * t_c, t_c);

  getDesiredValsInternal(t);
}


void Leg::getDesiredValsInternal(int t) { // assume t has been adjusted for phasing

  int forward = gait.leg_dir[id];
  float theta;
  float velocity;

  if (t < ts[1]) {
    theta = thetas[0] + t * recovery_speed;
    velocity = recovery_speed;
  }
  else if (t < ts[2]) {
    theta = thetas[1] + (t - ts[1]) * ground_speed;
    velocity = ground_speed;
  }
  else if (t < ts[3]) {
    theta = thetas[2] + (t - ts[2]) * ground_speed;
    velocity = ground_speed;
  }
  else {
    theta = thetas[3] + (t - ts[3]) * recovery_speed;
    velocity = recovery_speed;
  }

  if (theta < theta_up - theta_circle) theta = theta_circle + theta;
  else if (theta >= theta_up) theta = -theta_circle + theta; // wrap thetas
  theta = theta * forward;
  velocity = velocity * forward;
  global_theta = theta;
  global_velocity = velocity;

}
