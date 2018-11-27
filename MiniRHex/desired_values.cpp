
#include "control_parameters.h"
#include "desired_values.h"
#include <math.h>
#include <fstream>

vals get_desired_vals_internal(int t, leg l){
  //assume t has been adjusted for phasing

  int forward = l.forwards[l.gait - 1]; //standing is 0: -1 shifts to account for zero indexing
  float theta;
  float velocity;

  if (t < l.ts[1]){
    theta = l.thetas[0] + t * l.recovery_speed;
    velocity = l.recovery_speed;
  }
  else if (t < l.ts[2]){
    theta = l.thetas[1] + (t - l.ts[1]) * l.ground_speed;
    velocity = l.ground_speed;
  }
  else if (t < l.ts[3]){
    theta = l.thetas[2] + (t - l.ts[2]) * l.ground_speed;
    velocity = l.ground_speed;
  }
  else{
    theta = l.thetas[3] + (t - l.ts[3]) * l.recovery_speed;
    velocity = l.recovery_speed;
  }

  if (theta < theta_up - theta_circle) theta = theta_circle + theta;
  else if (theta >= theta_up) theta = -theta_circle + theta; //wrap thetas
  theta = theta * forward;
  velocity = velocity * forward;
  vals result = {theta, velocity};
  return result;
}

vals get_desired_vals(int t, leg l){ //handles phasing and start time, user provides get desired vals internal function
  int elapsed_time = t - l.startMillis;

  float phase = l.phase;
  t = fmodf(elapsed_time + phase * l.t_c, l.t_c);
  
  return get_desired_vals_internal(t, l);
}
