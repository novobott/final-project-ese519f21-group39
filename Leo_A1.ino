#include "I2C.h"
#include "MPU_6050.h"
#include "MPU_6050_reg.h"
#include "Flex.h"

#include <Mouse.h>
#include <Keyboard.h>

#define F_CPU 16000000UL
#include <avr/io.h>
#include <inttypes.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <math.h>

volatile int xPosition = 0, yPosition = 0;
int control = 0;
int key_press = 0;

void initialize_adc(){
  
  PRR0 &= ~(1<<PRADC);
  ADMUX = 0x40;
  //Select Vref = AVcc
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<REFS1);

  //Setup ADC Clock div by 128 -> 125KHz
  ADCSRA |= (1<<ADPS0);
  ADCSRA |= (1<<ADPS1);
  ADCSRA |= (1<<ADPS2);

  //Setting Conversion Bit to 0
  ADCSRA &= ~(1<<ADIF);

  //Set to auto trigger
  ADCSRA |= (1<<ADATE);

  //Disable Input Buffer on ADC PIN
  DIDR0 |= (1<<ADC0D);
  
  //Enable ADC
  ADCSRA |= (1<<ADEN);
  //Start Conversion
  ADCSRA |= (1<<ADSC);
  
}

uint16_t flex_resL, flex_resR;
uint8_t ret;
int mouseL, mouseR;
int16_t accel_buff[3], gyro_buff[3];
int vx, vy;
void setup() {

  Mouse.begin();
  Keyboard.begin();
  initialize_adc();
  Serial.begin(9600);
  DDRB |= (1<<0);
  sei();
  init_i2c();
  ret = i2c_start_w_address(MPU6050_ADDRESS + I2C_WRITE);
  if(ret == 0){
    PORTB |= (1<<0);
    _delay_ms(1000);
    PORTB &= ~(1<<0);
  }
  mpu6050_init();
  flex_init();
  //can read flex either directly using ADC or over I2c. 
}

void loop() {

  //flex_resL = flex_get_data(0); // mapping 0th cahnnel to left finger
  //flex_resR = flex_get_data(1); //mapping 1st channel to the right finger


  
  mpu6050_read_gyro_ALL(gyro_buff);

  vx = (gyro_buff[0]+300)/150;  // change 300 from 0 to 355
  vy = -(gyro_buff[2]-0)/150; // same here about "-100"  from -355 to 0

/*
  Serial.print("gx = ");
  Serial.print(gyro_buff[0]);
  
  Serial.print(" | gy = ");
  Serial.print(gyro_buff[1]);
  
  Serial.print(" | gz = ");
  Serial.print(gyro_buff[2]);
  Serial.print("\n");
*/
  Mouse.move(vx, vy);
  //delay(20);

   while(!(ADCSRA & (1<<ADIF)));
      if(key_press == 0){
      xPosition = ADC;
      Serial.println("Value of X is = ");
      Serial.print(xPosition);
      Serial.println(" ");
      ADMUX = 0x41; //read from A1
      _delay_ms(10);
      key_press = 1;
      ADCSRA |= (1<<ADEN);
      ADCSRA |= (1<<ADSC);
    }
     if(key_press == 1){
      yPosition = ADC;
      Serial.println("Value of Y is = ");
      Serial.print(yPosition);
      Serial.println(" ");
      ADMUX = 0x44; //read from A4
      _delay_ms(10);
      key_press = 2;
      ADCSRA |= (1<<ADEN);
      ADCSRA |= (1<<ADSC);
 
   }
    
    if(key_press == 2){
      mouseL = ADC; // this will be at anaog 3
      Serial.println("Value of Mouse Left is = ");
      Serial.print(mouseL);
      Serial.println(" ");
      ADMUX = 0x45;
      _delay_ms(10);
      key_press = 3;
      ADCSRA |= (1<<ADEN);
      ADCSRA |= (1<<ADSC);
   }

   if(key_press == 3){
      mouseR = ADC; // this will be at analog 2
      Serial.println("Value of Mouse Right is = ");
      Serial.print(mouseR);
      Serial.println(" ");
      
      ADMUX = 0x40;
      _delay_ms(10);
      key_press = 0;
      ADCSRA |= (1<<ADEN);
      ADCSRA |= (1<<ADSC);
    }


   if(mouseL < 620){
      Mouse.press(MOUSE_LEFT);
    }

    if(mouseR < 590){
      Mouse.press(MOUSE_RIGHT);
    }

    if (xPosition < 250 && (yPosition>250 && yPosition<750))
     {
     //Keyboard.releaseAll();
      Keyboard.press('a'); //for a
      //Keyboard.release('a');
     }
     
     else if (xPosition > 750 && (yPosition>250 && yPosition<750))
     {
     // Keyboard.releaseAll();
      Keyboard.press('d'); //for d
      //Keyboard.release('d');
     }
     
    else if (yPosition > 750 && (xPosition>250 && xPosition< 750))
    {
      //Keyboard.releaseAll();
      Keyboard.press('w'); //for w
      //Keyboard.releaseAll();
    }
 
    else if (yPosition < 250 && (xPosition>250 && xPosition< 750))
    {
      //Keyboard.releaseAll();
      Keyboard.press('s'); //for s
      //Keyboard.releaseAll();
    }  
    else{
      Keyboard.releaseAll();
      }
    //_delay_ms(20);

}
