/*
 * Flex.c
 *
 * Created: 12/18/2021 11:07:04 PM
 *  Author: arjun
 */ 
#include <inttypes.h>
#include <stdint.h>

#include "Flex.h"
#include "I2C.h"


//0 for device found
//1 if device not found
uint8_t flex_init(void)
{
	uint8_t res;
	res = i2c_start(flex_default_address+I2C_WRITE);
	
	i2c_start_wait(flex_default_address+I2C_WRITE);
	i2c_write(ADS1015_POINTER_CONFIG);
	uint16_t temp_data = 0b0000101010000001;
	i2c_write(temp_data >> 8);
	temp_data = temp_data & 0xFF;
	i2c_write(temp_data);
	i2c_stop();
	
}


//returns a zero when not functioning properly.
//returns analog output otherwise
uint16_t flex_get_data(uint8_t channel)
{
	
	uint16_t result;
	
	if(channel >= 2){return 0;}
	
	uint16_t config = ADS1015_CONFIG_OS_SINGLE | 0 | 0x0020; 
	//oring with 0 to set in continuous mode,
	//0x3300 represent s sampling rate of 3300Hz
	
	//Will return a different hex value for each gain
	//0x0E00: +/- 0.256V
	//0X0000: +/- 6.144V
	//0X0200: +/- 4.096V
	//0X0400: +/- 2.048V
	//0X0600: +/- 1.024V
	//0X0800: +/- 0.512V
	//0X0A00: +/- 0.256V
	config |= 0x0E00; //setting gain
	
	
	switch (channel){
		case(0):
			config |= ADS1015_CONFIG_MUX_SINGLE_0;
			break;
			
		case(1):
			config |= ADS1015_CONFIG_MUX_SINGLE_1;
	}
	
	//write_register()
	
	//i2c_write_bytes(flex_default_address, ADS1015_POINTER_CONVERT,2, *config);
		
	i2c_start_wait(flex_default_address+I2C_WRITE);
	i2c_write(ADS1015_POINTER_CONFIG);
	uint8_t temp_data = config>>8;
	i2c_write(temp_data);
	temp_data = config & 0xFF;
	i2c_write(temp_data);
	i2c_stop();
	
	uint8_t req_res[2];
	
	i2c_start_wait(flex_default_address+I2C_WRITE);
	i2c_write(ADS1015_POINTER_CONVERT);
	i2c_rep_start(flex_default_address+I2C_READ);
	
	req_res[1] = i2c_readAck();
	req_res[0] = i2c_readNak();
	i2c_stop();
	
	result = req_res[1] | (req_res[0] << 8 );
	result = result >> 4;
	return result;
	
}