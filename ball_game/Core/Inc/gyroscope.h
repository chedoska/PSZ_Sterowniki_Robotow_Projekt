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

struct L3GD20
{
	SPI_HandleTypeDef *hspi_handle;
	int16_t X_raw;
	int16_t Y_raw;
	int16_t Z_raw;
};

extern struct L3GD20 L3GD20_data;

int L3GD20_init(SPI_HandleTypeDef *hspi_handle);
void L3GD20_send(uint8_t address, uint8_t data);
uint8_t L3GD20_recive(uint8_t addres);
void L3GD20_readRawData();

#endif /* GYROSCOPE_H_ */
