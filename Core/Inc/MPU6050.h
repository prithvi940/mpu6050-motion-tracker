#ifndef MPU6050_H
#define MPU6050_H

#define MPU6050 0xD0

void MPU6050_init(void);

void read_accel(float* ax, float* ay, float* az);

void read_gyro(float* gx, float* gy, float* gz);

void calculate_angle(void);

void FoundDevices(void);


#endif
