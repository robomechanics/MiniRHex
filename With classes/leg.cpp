#include "leg.h"

float theta_circle = 360; //theta for one revolution
float theta_dead = 60; //theta range of deadzone
float theta_up = 180; //theta of middle of deadzone


void leg::update_gait(gait_params new_gait, int startMillis, leg_params the_leg, int gait_num) {
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


void leg::update_gait_internal_params(int startTime) {
	float ground_speed;
	float recovery_speed;
	int t_s = round(t_c * duty_factor);

	if (gait == PRONK) {
		ground_speed = theta_slow / t_s;
		recovery_speed = -theta_slow / (t_c - t_s);

		thetas[0] = theta_down;
		ts[0] = 0;

		thetas[1] = theta_down - theta_slow / 2;
		ts[1] = ts[0] + (thetas[1] - thetas[0]) / recovery_speed;

		thetas[2] = theta_down;
		ts[2] = ts[1] + (thetas[2] - thetas[1]) / ground_speed;

		thetas[3] = theta_down + theta_slow / 2;
		ts[3] = ts[2] + (thetas[3] - thetas[2]) / ground_speed;

		thetas[4] = theta_down;
		ts[4] = t_c;

	}
	else { //all walking gaits (and standing technically)

		ground_speed = theta_slow / t_s;
		recovery_speed = (theta_circle - theta_slow) / (t_c - t_s);

		thetas[0] = theta_down - theta_circle + theta_up;
		ts[0] = 0;

		thetas[1] = theta_down - theta_slow / 2;
		ts[1] = ts[0] + (thetas[1] - thetas[0]) / recovery_speed;

		thetas[2] = theta_down;
		ts[2] = ts[1] + (thetas[2] - thetas[1]) / ground_speed;

		thetas[3] = theta_down + theta_slow / 2;
		ts[3] = ts[2] + (thetas[3] - thetas[2]) / ground_speed;

		thetas[4] = theta_down + theta_up;
		ts[4] = t_c;

	}
	startMillis = startTime;

}

void leg::get_desired_vals_internal(int t) {
	//assume t has been adjusted for phasing

	int forward = params.forwards[gait]; //standing is 0: -1 shifts to account for zero indexing
	float new_theta;
	float new_velocity;
	if (t < ts[1]) {
		new_theta = thetas[0] + t * recovery_speed;
		new_velocity = recovery_speed;
	}
	else if (t < ts[2]) {
		new_theta = thetas[1] + (t - ts[1]) * ground_speed;
		new_velocity = ground_speed;
	}
	else if (t < ts[3]) {
		new_theta = thetas[2] + (t - ts[2]) * ground_speed;
		new_velocity = ground_speed;
	}
	else {
		new_theta = thetas[3] + (t - ts[3]) * recovery_speed;
		new_velocity = recovery_speed;
	}

	if (new_theta < theta_up - theta_circle) new_theta = theta_circle + new_theta;
	else if (new_theta >= theta_up) new_theta = -theta_circle + new_theta; //wrap thetas
	des_theta = new_theta * forward;
	des_vel = new_velocity * forward;
	update_pd_controller();
}

void leg::get_desired_vals(int t) { //handles phasing and start time, user provides get desired vals internal function
	int elapsed_time = t - startMillis;

	float phase = phase;
	t = fmodf(elapsed_time + phase * t_c, t_c);

	return get_desired_vals_internal(t);
}


float leg::get_control_signal(){
	float diff = fmod(theta_des - theta_act, theta_circle);
	float shortest_distance = theta_circle / 2 - fabs(fabs(diff) - theta_circle / 2);
	float dtheta = fmodf(diff + theta_circle, theta_circle) < theta_circle / 2 ? shortest_distance : -shortest_distance;
	float dv = (v_des - v_act);
	return kp * dtheta + kd * dv;
}

void leg::set_theta_act(float actual_theta){
	theta_act = actual_theta;
}

float leg::set_theta_act() {
	return theta_act;
}

void leg::set_vel_act(float actual_vel){
	velocity_act = acutal_vel;
}

float leg::set_vel_act() {
	return velocity_act;
}

void leg::set_kp(float new_kp) {
	kp = new_kp;
}
 
void leg::set_kp(float new_kd) {
	kd = new_kd;
}
