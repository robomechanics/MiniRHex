#include "pd_control.h"
#include "control_parameters.h"
#include <stdio.h>
#include <math.h>

//Implementation of pdcontrol with shortest path around a circle used for theta


//Different gains for walking and standing


float kp_hold = .008;
float kd_hold = 1.0;


//Attempts to send leg the short way around the circle to match desired position 
float pd_controller(float theta_act, float theta_des, float v_act, float v_des, float kp, float kd){
 	float diff = fmod(theta_des - theta_act, theta_circle);
 	float shortest_distance = theta_circle/2 - fabs(fabs(diff) - theta_circle/2);
 	float dtheta = fmodf(diff + theta_circle, theta_circle) < theta_circle/2 ? shortest_distance : -shortest_distance;
 	float dv = (v_des - v_act);
 	return kp * dtheta + kd * dv;
}
