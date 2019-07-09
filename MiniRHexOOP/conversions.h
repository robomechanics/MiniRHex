#ifndef _CONVERSIONS_H
#define _CONVERSIONS_H

// Inherent to design
extern float theta_circle; // theta for one revolution
extern float theta_dead; // theta range of deadzone
extern float theta_up; // theta of middle of deadzone

// V refers to units used in calculation (degrees per millisecond)
// dynV refers to command velocity sent to dynamixels (ranges from [0-2048), >1023 is opposite direction)

// All velocity conversions here are absolute //
// will have to convert from absolute to relative before utilizing //

float dynV_to_V(int dyn_V);
int V_to_dynV(float V);
float P_to_Theta(int P);
int Theta_to_P(float theta);
float ThetaR_to_Theta(float theta);
float Theta_to_ThetaR(float theta);
#endif
