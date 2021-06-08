#ifndef _TGAIT_PARAMETERS_H
#define _TGAIT_PARAMETERS_H
/*
 This struct defines the positions and timings of the tail. The tail commands are sent at the same times as the leg code
 An instance of this struct can be defined in gait.cpp and added as a variable inside the gait stuct
 */
struct tGait 
{
  //int id;
  bool first; //should always be set to true and will set be false during first run in the code
  float kp;
  float kd;
  float initial_delay; // This times it at a specific part of the legs period 
  float period; //amount of time at each tail location in milliseconds, probably want to go through all tail locations in one leg period
  int num_locs; // number of locations in the locations array
  int locations[10]; //these should be positions or angles and then converted to positions
  //in arduino there's no easy way to allocate a variable length array, so fill locations array with as many values as needed then pad with zeros
  int curr_loc_ind; // index in the locations array that tail is currently at. Should normally be initialized to 0 unless you want the tail to start somewhere other than the location at index 0
  int phase_inc; //if we should be incrementing up the locations or down the location array initially (usually 1, can be -1) 
  int count; //number of times the position of the tail has changed. Should be initialized as 0 always
};

#endif
