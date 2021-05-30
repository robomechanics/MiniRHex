#include "gait.h"
#include "leg.h"
#include "tgait.h" 

const float kp_walk = 0.03; // 0.02
const float kd_walk = 1.0;
const int walk_period = 2000; // 720;

/*
Explanation of parameters:

Duty Factor: Percentage of time the leg is in a standing position
(0 is always "fast", 1 is always "slow") (takes decimal values of 0-1)

Sweep: angle width of "slow phase" in degrees (takes integer values 0-360)

Down: center angle of the "slow phase" in degrees (takes integer values 0-360)

Phase: Determines the relative timing of the legs. Takes values from 0-1.
A phase of .5 will( have the leg at the opposite part of the cycle from a leg
with a phase of 0 ) (takes decimal values 0-1)
*/

//Leg 1 (Left Front) Parameters:
const float leg_dutyf = 0.42;
const float leg_sweep = 40.0;
const float leg_down = 20.0;
const float leg_phase1 = 0.50;
const float leg_phase2 = 0.0;


//Climbing parametrs

//Leg 1 (Left Front) Parameters for Climbing:
const float leg_dutyc = 0.7;
const float leg_sweepc = 60;
const float leg_downc = 280.0;
const float leg_phase1c = 0.50;
const float leg_phase2c = 0.0;
const float leg_phase3c = 0.25; 

const int walk_periodc = 5000; // 2000;
const int tail_period = 4000; 

// -------------------------------------- //


/*
 struct tGait 
{
  //int id;
  bool first; //should always be set to true and will set be false during first run
  float kp;
  float kd;
  float period; //amount of time at each tail location in milliseconds
  int num_locs; // number of locations in the locations array
  float locations[10]; //these should be positions or angles and then converted to positions
  int curr_loc_ind; 
  int phase_inc; //if we should be incrementing up the locations or down the location array
  int count; 
};

 */
//TAIL GAITS
int horizontal = 512;
int vertical = 768;
//position 512 is horizontal (parallel to the ground) 
const tGait no_tail { 
  true,
  0, 0,
  0,
  1000, //needs to be one because we mod by period,
  1,
  {512, 0, 0, 0, 0, 0,0,0,0,0},
  0,
  1,
  0
};
const tGait standard_tail { 
  true,
  kp_walk, kd_walk,
  0,
  5000, //milliseconds
  4,
  {512, 540, 560, 580, 0, 0, 0, 0, 0, 0}, // these are positions,
  0,
  1,
  0
};

const tGait climb_tail { 
  true,
  kp_walk, kd_walk,
  walk_periodc/3, 
  walk_periodc/2, //milliseconds
  2,
  {480, 380,0, 0, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail2 { 
  true,
  kp_walk, kd_walk,
  walk_periodc/3, 
  walk_periodc/5, //milliseconds
  3,
  {480, 380, 380, 0, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail3 { 
  true,
  kp_walk, kd_walk,
  walk_periodc/3, 
  walk_periodc/2, //milliseconds
  2,
  {480, 480, 0, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail4 { 
  true,
  kp_walk, kd_walk,
  walk_periodc/3, 
  walk_periodc/4, //milliseconds
  3,
  {480, 365, 300, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail5 { 
  true,
  kp_walk, kd_walk,
  7000/10, 
  7000/4, //milliseconds
  3,
  {490, 430, 400, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail6 { 
  true,
  kp_walk, kd_walk,
  7000/10, 
  7000/4, //milliseconds
  3,
  {390, 490, 430, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail7 { 
  true,
  kp_walk, kd_walk,
  7000/10, 
  7000/4, //milliseconds
  3,
  {435, 400, 490, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail8 { 
  true,
  kp_walk, kd_walk,
  7000/10, 
  7000/4, //milliseconds
  3,
  {420, 400, 490, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail9 { 
  true,
  kp_walk, kd_walk,
  7000/10, 
  7000/4, //milliseconds
  3,
  {410, 400, 490, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail10 { 
  true,
  kp_walk, kd_walk,
  7000/10, 
  7000/4, //milliseconds
  3,
  {440, 400, 490, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};

const tGait climb_tail11 { 
  true,
  kp_walk, kd_walk,
  7000/10, 
  7000/4, //milliseconds
  3,
  {470, 400, 490, 0, 0, 0, 0, 0, 0}, // these are angles,
  0,
  1,
  0
};
//----------------------------------------//
const Gait stand_gait {
    STAND,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {1, 1, 1, 1, 1, 1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase1, leg_phase1, leg_phase1, leg_phase1, leg_phase1},
    no_tail
    
};

const Gait walk_gait {
    WALK,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {1, 1, 1, 1, 1, 1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2},
    standard_tail
};

const Gait reverse_gait {
    REVERSE,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {-1, -1, -1, -1, -1, -1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2},
    no_tail
};

const Gait left_gait {
    LEFT,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {-1, -1, -1, 1, 1, 1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2},
    no_tail
};

const Gait right_gait {
    RIGHT,
    kp_walk, kd_walk,
    {leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep, leg_sweep},
    {leg_down, leg_down, leg_down, leg_down, leg_down, leg_down},
    {1, 1, 1, -1, -1, -1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf, leg_dutyf},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2},
    no_tail
};

const Gait climbing_gait {
    CLIMB,
    kp_walk, kd_walk,
    {leg_sweepc, leg_sweepc, leg_sweepc, leg_sweepc, leg_sweepc, leg_sweepc},
    {leg_downc, leg_downc, leg_downc, leg_downc, leg_downc, leg_downc},
    {-1, -1, -1, -1, -1, -1},
    {walk_period, walk_period, walk_period, walk_period, walk_period, walk_period},
    {leg_dutyc, leg_dutyc, leg_dutyc, leg_dutyc, leg_dutyc, leg_dutyc},
    {leg_phase1, leg_phase2, leg_phase1, leg_phase2, leg_phase1, leg_phase2},
    standard_tail
};

const Gait alt_fb { 
    CLIMB1,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 40, leg_sweepc, 1, 40},
    {leg_downc, 130, 250, leg_downc, 130, 250},
    {-1, -1, -1, -1, -1, -1},
    {walk_periodc, 1000000, walk_periodc, walk_periodc, 1000000, walk_periodc},
    {leg_dutyc, 1, 1, leg_dutyc, 1, 1},
    {leg_phase1, .25, leg_phase2, leg_phase1, .25, leg_phase2},
    climb_tail
};

const Gait climb3 { 
    CLIMB2,
    kp_walk, kd_walk,
    {leg_sweepc, 30, 30, leg_sweepc, 30, 30},
    {leg_downc, 100, 100, leg_downc, 100, 100},
    {-1, 1, 1, -1, 1, 1},
    {walk_periodc, walk_periodc, walk_periodc, walk_periodc, walk_periodc, walk_periodc},
    {leg_dutyc, 1, 1, leg_dutyc, 1, 1},
    {leg_phase1, .33, .33, leg_phase1,.33, .33},
    climb_tail
};

const Gait alt_fb_static { 
    CLIMB3,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 50, leg_sweepc, 1, 50},
    {leg_downc, 130, 275, leg_downc, 130, 275},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, -1, -1, -1, -1},
    {walk_periodc, 1000000, walk_periodc, walk_periodc, 1000000, walk_periodc},
    {leg_dutyc, 1, 1, leg_dutyc, 1, 1},
    {leg_phase1, .25, 0, leg_phase1, .25, 0},
    climb_tail2
};

const Gait full_rot { 
    CLIMB4,
    kp_walk, kd_walk,
    {leg_sweepc, 1, leg_sweepc, leg_sweepc, 1, leg_sweepc},
    {leg_downc, 130, leg_downc, leg_downc, 130, leg_downc},
    {-1, -1, -1, -1, -1, -1},
    {walk_periodc, 1000000, walk_periodc, walk_periodc, 1000000, walk_periodc},
    {leg_dutyc, 1, leg_dutyc, leg_dutyc, 1, leg_dutyc},
    {0, .25, .5, 0, .25, .5},
    climb_tail3
};

const Gait climb5{
    CLIMB5,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 50, leg_sweepc, 1, 50},
    {290, 130, 275, 290, 130, 275},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, -1, -1, -1, -1},
    {walk_periodc, 1000000, walk_periodc, walk_periodc, 1000000, walk_periodc},
    {leg_dutyc, 1, 1, leg_dutyc, 1, 1},
    {leg_phase1, .2, 0, leg_phase1, .2, 0},
    climb_tail4
};

const Gait climb6{
    CLIMB6,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 70, leg_sweepc, 1, 70},
    {300, 130, 260, 300, 130, 260},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, -1, -1, -1, -1},
    {walk_periodc, 1000000, walk_periodc, walk_periodc, 1000000, walk_periodc},
    {leg_dutyc, 1, 1, leg_dutyc, 1, 1},
    {leg_phase1, .1, .2, leg_phase1, .1, .2},
    climb_tail4
};


const Gait climb7{
    CLIMB7,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 70, leg_sweepc, 1, 70},
    {300, 130, 260, 300, 130, 260},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, -1, -1, -1, -1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .1, .28, leg_phase1, .1, .28},
    climb_tail4
};

const Gait climb8{
    CLIMB7,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 100, 300, 130, 100},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .85, leg_phase1, .9, .85},
    climb_tail5
};

const Gait climb9{
    CLIMB8,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 100, 300, 130, 100},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .8, leg_phase1, .9, .8},
    climb_tail6
};

const Gait climb10{ //DO NOT CHANGE WORKS AT 50 DEGREES WITH CORKBOARD
    CLIMB9,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 100, 300, 130, 100},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .8, leg_phase1, .9, .8},
    climb_tail7
};

const Gait climb11{ //works for 55
    CLIMB10,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 90, 300, 130, 90},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .8, leg_phase1, .9, .8},
    climb_tail8
};

const Gait climb12{ 
    CLIMB11,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 80, 300, 130, 80},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .8, leg_phase1, .9, .8},
    climb_tail8
};

const Gait climb13{ //sort of working for 60
    CLIMB12,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 35, leg_sweepc, 1, 35},
    {300, 130, 80, 300, 130, 80},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .8, leg_phase1, .9, .8},
    climb_tail9
};


const Gait climb14{ //works for 55
    CLIMB13,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 80, 300, 130, 80},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .9, leg_phase1, .9, .9},
    climb_tail10
};

const Gait climb15{ //works for 55
    CLIMB14,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 70, 300, 130,70},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .9, leg_phase1, .9, .9},
    climb_tail11
};

const Gait climb16{ //works for 55
    CLIMB15,
    kp_walk, kd_walk,
    {leg_sweepc, 1, 20, leg_sweepc, 1, 20},
    {300, 130, 88, 300, 130, 88},//  {leg_downc, 130, 265, leg_downc, 130, 265},
    {-1, -1, 1, -1, -1, 1},
    {7000, 1000000, 7000, 7000, 1000000, 7000},
    {.5, 1, 1, .5, 1, 1},
    {leg_phase1, .9, .8, leg_phase1, .9, .8},
    climb_tail8
};
const Gait gait_order[TOTAL_GAITS] = {stand_gait, climb11}; //, reverse_gait, left_gait, right_gait};
