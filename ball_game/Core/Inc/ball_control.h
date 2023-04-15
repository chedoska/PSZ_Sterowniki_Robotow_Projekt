/*
 * ball_control.h
 *
 *  Created on: Apr 15, 2023
 *      Author: chedo
 */

#ifndef INC_BALL_CONTROL_H_
#define INC_BALL_CONTROL_H_

#include "gyroscope.h"

struct Ball_control_data
{
	float ctrlX_angle;
	float ctrlY_angle;
	float ctrlZ_angle;
	uint16_t X_screen_pos;
	uint16_t Y_screen_pos;
} typedef Ball_control_data;

void ball_ctrl_init(Ball_control_data *ball_data, uint16_t X_start_pos, uint16_t Y_start_pos);
void ball_ctrl_restetDrift(Ball_control_data *ball_data);
void ball_update_ctrl_angles(Ball_control_data *ball_data, L3GD20 *L3GD20_data, int delta_time_ms);
void ball_update_pos(Ball_control_data *ball_data, int delta_time_ms);

#endif /* INC_BALL_CONTROL_H_ */
