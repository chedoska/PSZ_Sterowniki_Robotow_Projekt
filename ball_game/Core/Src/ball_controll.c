/*
 * ball_controll.c
 *
 *  Created on: Apr 15, 2023
 *      Author: chedo
 */
#include "ball_control.h"

void ball_ctrl_init(Ball_control_data *ball_data, uint16_t X_start_pos, uint16_t Y_start_pos)
{
	ball_ctrl_restetDrift(ball_data);
	ball_data->X_screen_pos = X_start_pos;
	ball_data->Y_screen_pos = Y_start_pos;
	ball_data->X_screen_speed = 0;
	ball_data->Y_screen_speed = 0;
}

void ball_ctrl_restetDrift(Ball_control_data *ball_data)
{
	ball_data->ctrlX_angle = 0;
	ball_data->ctrlY_angle = 0;
	ball_data->ctrlY_angle = 0;
}

void ball_update_ctrl_angles(Ball_control_data *ball_data, L3GD20 *L3GD20_data, int delta_time_ms)
{
	float delta_time = delta_time_ms / 1000.0;
	ball_data->ctrlX_angle += L3GD20_data->X_val * delta_time;
	ball_data->ctrlY_angle += L3GD20_data->Y_val * delta_time;
	ball_data->ctrlZ_angle += L3GD20_data->Z_val * delta_time;
}

void ball_update_pos(Ball_control_data *ball_data, int delta_time_ms)
{
	float delta_time = delta_time_ms / 1000.0;
	float X_radAngle = (ball_data->ctrlX_angle * PI_CONST / 180.0);
	float Y_radAngle = (ball_data->ctrlY_angle * PI_CONST / 180.0);

	ball_data->X_screen_speed += sinf(X_radAngle) * GRAVITY_CONST * delta_time;
	ball_data->Y_screen_speed += sinf(Y_radAngle) * GRAVITY_CONST * delta_time;

	if(ball_data->X_screen_speed > 0)
		ball_data->X_screen_speed -= FRICTION_CONST * delta_time;
	else
		ball_data->X_screen_speed += FRICTION_CONST * delta_time;

	if(ball_data->Y_screen_speed > 0)
			ball_data->Y_screen_speed -= FRICTION_CONST * delta_time;
		else
			ball_data->Y_screen_speed += FRICTION_CONST * delta_time;

	ball_data->X_screen_pos += (ball_data->X_screen_speed * delta_time);
	ball_data->Y_screen_pos += (ball_data->Y_screen_speed * delta_time);
}







