/*
 * MPU6050.c
 *
 *  Created on: Apr 7, 2026
 *      Author: pruth
 */


#include "main.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

#define MPU6050 0xD0
#define PI 3.14

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void MPU6050_init(void){
	//	1 Power Management
	uint8_t data = 0x00;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050, 0x6B, 1, &data, 1, HAL_MAX_DELAY);

	//	2 Setting Clock
	data = 0x01;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050, 0x6B, 1, &data, 1, HAL_MAX_DELAY);

	//	3 ACCEL Config
	data = 0x00;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050, 0x1C, 1, &data, 1, HAL_MAX_DELAY);

	//	4 GYRO Config
	data = 0x00;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050, 0x1B, 1, &data, 1, HAL_MAX_DELAY);

	//	5 Digital LPF
	data = 0x03;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050, 0x1A, 1, &data, 1, HAL_MAX_DELAY);

	// 6 Sampling Rate Selection
	data = 0x07;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050, 0x19, 1, &data, 1, HAL_MAX_DELAY);
}

void read_accel(float* ax, float* ay, float* az){
	uint8_t accel_raw[6];

	HAL_I2C_Mem_Read(&hi2c1, MPU6050, 0x3B, 1, accel_raw, 6, HAL_MAX_DELAY);

	int16_t raw_ax = (int16_t)(accel_raw[0] << 8 | accel_raw[1]);
	int16_t raw_ay = (int16_t)(accel_raw[2] << 8 | accel_raw[3]);
	int16_t raw_az = (int16_t)(accel_raw[4] << 8 | accel_raw[5]);

	*ax = raw_ax / 16384.0;
	*ay = raw_ay / 16384.0;
	*az = raw_az / 16384.0;
}

void read_gyro(float* gx, float* gy, float* gz){
	uint8_t gyro_raw[6];

	HAL_I2C_Mem_Read(&hi2c1, MPU6050, 0x43, 1, gyro_raw, 6, HAL_MAX_DELAY);

	int16_t raw_gx = (int16_t)(gyro_raw[0] << 8 | gyro_raw[1]);
	int16_t raw_gy = (int16_t)(gyro_raw[2] << 8 | gyro_raw[3]);
	int16_t raw_gz = (int16_t)(gyro_raw[4] << 8 | gyro_raw[5]);

	*gx = raw_gx / 131.0;
	*gy = raw_gy / 131.0;
	*gz = raw_gz / 131.0;
}

void FoundDevices(void){
	uint8_t i;
	for(i = 0;i < 128;i++){
		if(HAL_I2C_IsDeviceReady(&hi2c1, i<<1, 1, 100) == HAL_OK){
			char msg[40];
			sprintf(msg, "Device Found at : %X\r\n", i);
			HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 100);
		}
	}
	HAL_Delay(2000);
}
