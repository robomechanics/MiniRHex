#ifndef desired_values
#define desired_values

#include "leg_info.h"

typedef struct desired_vals_container vals;

// Struct provides easy way to return both vals without pointers //
struct desired_vals_container{
  float global_theta;
  float global_velocity;
};

vals get_desired_vals(int t, leg l);

extern float recovery_speed;

#endif
