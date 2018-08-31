#pragma once
#ifndef leg
#define leg

#include <math.h>
#include <fstream>

struct gait_params {
	float theta_s;  //sweep
	float theta_d;  //down
	int t_cc;       //period
	float duty_f;   //duty factor
	float phases[7];   //phases
	float kp;
	float kd;
};


float theta_circle; //theta for one revolution
float theta_dead; //theta range of deadzone
float theta_up; //theta of middle of deadzone
/*struct control_params {
	float theta_circle; //theta for one revolution
	float theta_dead; //theta range of deadzone
	float theta_up; //theta of middle of deadzone
};

control_params cont_params = { 360,60,180 };*/

struct leg_params {
	int id;              //leg number
	float desired_theta; //only utilized in position control mode
	int forwards[6];	 //changeable, direction of rotation in current gait
	float zero;			 //zero position
	bool right_side;	 //if right side we must convert absolute velocity and theta to relative velocity theta
	bool deadzone;		 //true if leg is currently in deadzone
	bool dead_from_neg;
};

class leg {
private:
	/*float theta_circle = cont_params[0]; //theta for one revolution
	float theta_dead = cont_params[1]; //theta range of deadzone
	float theta_up = cont_params[2]; //theta of middle of deadzone*/
	
	const int STAND = 0;
	const int WALK = 1;
	const int LEFT = 2;
	const int REVERSE = 3;
	const int RIGHT = 4;
	const int PRONK = 5;

	
	int gait;
	//Needs updated with each gait change

	float theta_slow;
	float theta_down;
	int t_c;
	float duty_factor;
	float phase;
	int startMillis;
	float kp;
	float kd;
	float des_theta;
	float des_vel;
	float theta_act;
	float velocity_act;

	//computed from above in internal params

	float recovery_speed;
	float ground_speed;
	float thetas[5]; //0 through 4
	float ts[5]; //0 through 4

public:


	
	leg_params params;


	void update_gait_internal_params(int startTime);
	void get_desired_vals(int t);
	float get_control_signal();
	void set_theta_act(float actual_theta);
	float get_theta_act();
	void set_vel_act(float actual_vel);
	float get_vel_act();
	void set_kp(float new_kp);
	void set_kp(float new_kd);
	void update_gate(gait_params new_gait, int startMillis, leg_params the_leg, int gait_num);
	leg();

	leg(gait_params new_gait, int startMillis, leg_params the_leg, int gait_num) {
		printf("Gait %d\n", new_gait.t_cc);
		params = the_leg;
		gait = gait_num;
		theta_slow = new_gait.theta_s;
		theta_down = new_gait.theta_d;
		t_c = new_gait.t_cc;
		duty_factor = new_gait.duty_f;
		phase = new_gait.phases[id];
		kp = new_gait.kp;
		kd = new_gait.kd;
		update_gait_internal_params(startMillis);
	}
};




#endif