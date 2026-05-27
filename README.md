# mpu6050-motion-tracker

Real-time roll and pitch estimation using MPU6050 and STM32 with live 3D visualization in Python.

## Features

- MPU6050 interfacing using I2C
- Roll and pitch estimation
- Complementary filter implementation
- Accelerometer and gyroscope calibration
- Real-time UART data streaming
- Live 3D plane animation in Python

## Hardware Used

- STM32 Nucleo / STM32F4 Board
- MPU6050 IMU Sensor

## Software Used

### Embedded
- STM32CubeIDE
- STM32 HAL
- C

### Visualization
- Python
- NumPy
- Matplotlib
- PySerial

## Working

- Accelerometer provides absolute orientation but is noisy
- Gyroscope provides smooth motion but drifts over time
- A complementary filter combines both for stable orientation tracking

## Challenges Faced

- Incorrect `dt` caused gyro integration errors
- Degree/radian conversion mismatch
- Axis mapping and sign convention issues
- Gyroscope drift and accelerometer noise
- Real-time synchronization between STM32 and Python visualization

## Project Structure

```text
├── Core/
│   ├── Inc/
│   └── Src/
│
├── Python_Visualization/
│   └── imu_visualization.py
│
├── MPU6050.ioc
├── README.md
└── .gitignore
```

##Installation
```bash
pip install matplotlib numpy pyserial
```
