/*
 * gyroscope.c
 *
 *  Created on: 15 kwi 2023
 *      Author: chedo
 */
#include "gyroscope.h"

struct L3GD20 L3GD20_data;

int L3GD20_init(SPI_HandleTypeDef *m_hspi_handle){
	L3GD20_data.hspi_handle = m_hspi_handle;

	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);

	if(L3GD20_recive(L3GD20_WHO_AM_I) != 212)
	{
		return 0;
	}

	L3GD20_send(L3GD20_CTRL_REG1, 0x0F); // aktywuje żyroskop
	L3GD20_send(L3GD20_CTRL_REG4, 0x20); // Okreslenie skali
	L3GD20_send(L3GD20_CTRL_REG2, 0x00); // ustawia filtr górnoprzepustowy
	L3GD20_send(L3GD20_CTRL_REG5, 0x10); // włącza filtr górnoprzepustowy

	return 1;


	/*uint8_t recive_var[2];
	uint8_t address_var[2];

	address_var[0] = 0x00 | L3GD20_CTRL_REG1;
	address_var[1] = 0x0F;
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi5, address_var, 2, 500);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);

	address_var[0] = 0x00 | L3GD20_CTRL_REG4;
	address_var[1] = 0x10;
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi5, address_var, 2, 500);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);

	address_var[0] = 0x00 | L3GD20_CTRL_REG2;
	address_var[1] = 0x00;
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi5, address_var, 2, 500);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);

	address_var[0] = 0x00 | L3GD20_CTRL_REG5;
	address_var[1] = 0x10;
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi5, address_var, 2, 500);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);*/
}

void L3GD20_send(uint8_t address, uint8_t data)
{
	uint8_t transmit_data[2];
	transmit_data[0] = address;
	transmit_data[1] = data;
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(L3GD20_data.hspi_handle, transmit_data, 2, L3GD20_SPI_WAIT_TIME);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
}

uint8_t L3GD20_recive(uint8_t addres)
{
	uint8_t transmit_data[2];
	uint8_t recive_data[2];
	transmit_data[0] = addres | 0x80;
	transmit_data[1] = 0;
	recive_data[1] = 0;
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(L3GD20_data.hspi_handle, transmit_data, recive_data, 2, L3GD20_SPI_WAIT_TIME);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
	return recive_data[1];
}

void L3GD20_readRawData()
{
	L3GD20_data.X_raw = L3GD20_recive(L3GD20_OUT_X_L);
	L3GD20_data.X_raw |= L3GD20_recive(L3GD20_OUT_X_H) << 8;

	L3GD20_data.Y_raw = L3GD20_recive(L3GD20_OUT_Y_L);
	L3GD20_data.Y_raw |= L3GD20_recive(L3GD20_OUT_Y_H) << 8;

	L3GD20_data.Z_raw = L3GD20_recive(L3GD20_OUT_Z_L);
	L3GD20_data.Z_raw |= L3GD20_recive(L3GD20_OUT_Z_H) << 8;
}













