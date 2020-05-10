#include "conversions.h"

//Inherent to design
const unsigned short theta_circle = 360; //theta for one revolution
const unsigned short theta_dead = 60; //theta range of deadzone
const unsigned short theta_up = 180; //theta of middle of deadzone

//VMaxed tuned on xl320, roughly accurate
const float VMax = 0.8; //ratio of degrees per ms to dynamixel speed units

float dynV_to_V(int dynV) {
	float result = dynV;
  if (dynV > 1023) result = 1024 - dynV; //send negatives to negative
  result = result * VMax / 1024.0; //scale to appropriate VMax
  return result;
}

int V_to_dynV(float V) {
  // ensure no overflow
  float VMin = (V<VMax)?V:VMax;
  V = (VMin>-VMax)?VMin:-VMax;
  int result = V/VMax * 1023; // scale to appropriate range
  if (result < 0) result = 1024 - result; // handle negatives
  return result;
}

float P_to_Theta(int P) {
  return P * (theta_circle - theta_dead) / 1024 - 5 * (theta_circle) / 12.0; // (5*theta_circle/12) offsets 0 to bottom
}

int Theta_to_P(float theta) {
	int P = 512 + theta * 1024/(theta_circle - theta_dead);// 512 offsets 0 to bottom
	if (P < 0) return 0;
	if (P > 1023) return 1023;
	return P;
}

float Theta_to_ThetaR(float theta) {
  return -theta;//fmodf(theta+theta_circle, theta_circle) - theta_circle/2;
}

float ThetaR_to_Theta(float thetaR) {
  return -thetaR;//fmodf(theta+theta_circle, theta_circle) - theta_circle/2;
}
