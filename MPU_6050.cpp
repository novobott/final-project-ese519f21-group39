/*
 * MPU_6050.c
 *
 * Created: 12/19/2021 10:49:04 AM
 *  Author: arjun
 */ 
#include <inttypes.h>
#include <stdint.h>

#include "I2C.h"
#include "MPU_6050.h"
#include "MPU_6050_reg.h"
#include <inttypes.h>
#include <stdint.h>


uint8_t mpu6050_start(void){

	uint8_t res;
	res = i2c_start_w_address(MPU6050_ADDRESS+I2C_WRITE);
	if(~res){
		i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, &res);
		
		if(res==0x68){
			return res;
			}else{
			return 0;
		}
		}else{
		return 0;
	}
}




void mpu6050_init(void){
	
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, 0x00); //exit sleep mode
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_CONFIG, 0x01); // 
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG, 0x00); // gyro ADC scale: 250 deg/s
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, 0x00); //accel ADC scale: 2 g // not using accel values though
	
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_INT_ENABLE, 0x00); //enable data ready interrupt
	i2c_write_byte(MPU6050_ADDRESS, MPU6050_RA_SIGNAL_PATH_RESET, 0x00); //don't reset signal path

}




void mpu6050_read_gyro_ALL(int16_t * buff){
	
	uint8_t tmp[2];

	mpu6050_read_gyro_X(tmp);
	buff[0] = (tmp[0]<<8)|(tmp[1]);
	mpu6050_read_gyro_Y(tmp);
	buff[1] = (tmp[0]<<8)|(tmp[1]);
	mpu6050_read_gyro_Z(tmp);
	buff[2] = (tmp[0]<<8)|(tmp[1]);
}



void mpu6050_read_accel_ALL(int16_t * buff){
	
	uint8_t tmp[2];

	mpu6050_read_accel_X(tmp);
	buff[0] = (tmp[0]<<8)|(tmp[1]);
	mpu6050_read_accel_Y(tmp);
	buff[1] = (tmp[0]<<8)|(tmp[1]);
	mpu6050_read_accel_Z(tmp);
	buff[2] = (tmp[0]<<8)|(tmp[1]);
}






void mpu6050_read_gyro_X(uint8_t * buff){

	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_H, buff);
	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_XOUT_L, buff+1);
}


void mpu6050_read_gyro_Y(uint8_t * buff){

	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_H, buff);
	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_YOUT_L, buff+1);
}


void mpu6050_read_gyro_Z(uint8_t * buff){

	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_H, buff);
	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_GYRO_ZOUT_L, buff+1);
}




void mpu6050_read_accel_X(uint8_t * buff){

	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_H, buff);
	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_XOUT_L, buff+1);
}


void mpu6050_read_accel_Y(uint8_t * buff){

	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_H, buff);
	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_YOUT_L, buff+1);
}


void mpu6050_read_accel_Z(uint8_t * buff){

	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_H, buff);
	i2c_read_byte(MPU6050_ADDRESS, MPU6050_RA_ACCEL_ZOUT_L, buff+1);
}
