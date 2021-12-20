/*
 * Flex.h
 *
 * Created: 12/18/2021 11:06:50 PM
 *  Author: arjun
 */ 


#ifndef FLEX_H_
#define FLEX_H_

#define flex_default_address 0b10010000 //shifted address

#define ADS1015_DELAY                (1)

//Pointer Register
#define ADS1015_POINTER_CONVERT      (0x00)
#define ADS1015_POINTER_CONFIG       (0x01)
#define ADS1015_POINTER_LOWTHRESH    (0x02)
#define ADS1015_POINTER_HITHRESH     (0x03)

#define ADS1015_CONFIG_OS_NO         (0x8000)
#define ADS1015_CONFIG_OS_SINGLE     (0x8000)
#define ADS1015_CONFIG_OS_READY      (0x0000)
#define ADS1015_CONFIG_OS_NOTREADY   (0x8000)

#define ADS1015_CONFIG_MODE_CONT     (0x0000)
#define ADS1015_CONFIG_MODE_SINGLE   (0x0100)

#define ADS1015_CONFIG_MUX_SINGLE_0    (0x4000)
#define ADS1015_CONFIG_MUX_SINGLE_1    (0x5000)
#define ADS1015_CONFIG_MUX_SINGLE_2    (0x6000)
#define ADS1015_CONFIG_MUX_SINGLE_3    (0x7000)
#define ADS1015_CONFIG_MUX_DIFF_P0_N1  (0x0000)
#define ADS1015_CONFIG_MUX_DIFF_P0_N3  (0x1000)
#define ADS1015_CONFIG_MUX_DIFF_P1_N3  (0x2000)
#define ADS1015_CONFIG_MUX_DIFF_P2_N3  (0x3000)


#define ADS1015_CONFIG_RATE_128HZ    (0x0000)
#define ADS1015_CONFIG_RATE_250HZ    (0x0020)
#define ADS1015_CONFIG_RATE_490HZ    (0x0040)
#define ADS1015_CONFIG_RATE_920HZ    (0x0060)
#define ADS1015_CONFIG_RATE_1600HZ   (0x0080)
#define ADS1015_CONFIG_RATE_2400HZ   (0x00A0)
#define ADS1015_CONFIG_RATE_3300HZ   (0x00C0)

#define ADS1015_CONFIG_PGA_MASK      (0X0E00)
#define ADS1015_CONFIG_PGA_TWOTHIRDS       (0X0000)  // +/- 6.144v
#define ADS1015_CONFIG_PGA_1         (0X0200)  // +/- 4.096v
#define ADS1015_CONFIG_PGA_2         (0X0400)  // +/- 2.048v
#define ADS1015_CONFIG_PGA_4         (0X0600)  // +/- 1.024v
#define ADS1015_CONFIG_PGA_8         (0X0800)  // +/- 0.512v
#define ADS1015_CONFIG_PGA_16        (0X0A00)  // +/- 0.256v

#define ADS1015_CONFIG_CMODE_TRAD   (0x0000)  // Traditional comparator with hysteresis (default)
#define ADS1015_CONFIG_CMODE_WINDOW (0x0010)  // Window comparator
#define ADS1015_CONFIG_CPOL_ACTVLOW (0x0000)  // ALERT/RDY pin is low when active (default)
#define ADS1015_CONFIG_CPOL_ACTVHI  (0x0008)  // ALERT/RDY pin is high when active
#define ADS1015_CONFIG_CLAT_NONLAT  (0x0000)  // Non-latching comparator (default)
#define ADS1015_CONFIG_CLAT_LATCH   (0x0004)  // Latching comparator
#define ADS1015_CONFIG_CQUE_1CONV   (0x0000)  // Assert ALERT/RDY after one conversions
#define ADS1015_CONFIG_CQUE_2CONV   (0x0001)  // Assert ALERT/RDY after two conversions
#define ADS1015_CONFIG_CQUE_4CONV   (0x0002)  // Assert ALERT/RDY after four conversions
#define ADS1015_CONFIG_CQUE_NONE    (0x0003)  // Disable the comparator and put ALERT/RDY in high state (default)


uint8_t flex_init(void);
uint16_t flex_get_data(uint8_t channel);


#endif /* FLEX_H_ */