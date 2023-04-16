/*
 * gyroscope.h
 *
 *  Created on: 15 kwi 2023
 *      Author: chedo
 */

#include "main.h"

#ifndef GYROSCOPE_H_
#define GYROSCOPE_H_

#define L3GD20_CTRL_REG1 0x20
#define L3GD20_CTRL_REG2 0x21
#define L3GD20_CTRL_REG3 0x22
#define L3GD20_CTRL_REG4 0x23
#define L3GD20_CTRL_REG5 0x24

#define L3GD20_OUT_X_L 0x28
#define L3GD20_OUT_X_H 0x29
#define L3GD20_OUT_Y_L 0x2A
#define L3GD20_OUT_Y_H 0x2B
#define L3GD20_OUT_Z_L 0x2C
#define L3GD20_OUT_Z_H 0x2D

#define L3GD20_WHO_AM_I 0x0F

#define L3GD20_SPI_WAIT_TIME 500

#define L3GD20_X_OFFSET -30
#define L3GD20_Y_OFFSET -5
#define L3GD20_Z_OFFSET 13
#define SENSITIVITY 0.09

struct L3GD20
{
	SPI_HandleTypeDef *hspi_handle;
	int16_t X_raw;
	int16_t Y_raw;
	int16_t Z_raw;
	float X_val;
	float Y_val;
	float Z_val;
} typedef L3GD20;

extern struct L3GD20 L3GD20_data;

int L3GD20_init(SPI_HandleTypeDef *hspi_handle, L3GD20 *L3GD20_data);
void L3GD20_send(uint8_t address, uint8_t data, L3GD20 *L3GD20_data);
uint8_t L3GD20_recive(uint8_t addres, L3GD20 *L3GD20_data);
void L3GD20_readRawData(L3GD20 *L3GD20_data);
void L3GD20_convertRawData(L3GD20 *L3GD20_data);

#endif /* GYROSCOPE_H_ */