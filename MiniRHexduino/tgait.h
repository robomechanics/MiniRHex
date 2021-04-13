#ifndef _TGAIT_PARAMETERS_H
#define _TGAIT_PARAMETERS_H

struct tGait 
{
  //int id;
  bool first; //should always be set to true and will set be false during first run
  float kp;
  float kd;
  //float init_pos; //initial tail position is first in num_phases
 // float num_phases; //number of discrete tail positions
  float initial_delay; // to time it at a specific part of the legs period 
  float period; //amount of time at each tail location in milliseconds, usually same as one of the leg periods
  int num_locs; // number of locations in the locations array
  int locations[10]; //these should be positions or angles and then converted to positions
  int curr_loc_ind; 
  int phase_inc; //if we should be incrementing up the locations or down the location array
  int count; 
};

#endif
