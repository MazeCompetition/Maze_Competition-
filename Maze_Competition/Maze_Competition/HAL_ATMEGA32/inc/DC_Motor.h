/*
 * DC_Motor.h
 *
 * Created: 8/14/2023 11:15:01 AM
 *  Author: Bishoy Refaat
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_




//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|

#include "ATMEGA32.h"
#include "GPIO.h"
#include "TIMERs.h"

//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|
#define direction_right  0
#define direction_left   1





//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|

#define PORTx       PORTA
#define PinNum1     GPIO_PinNumber_0
#define PinNum2     GPIO_PinNumber_1
#define PinNum3     GPIO_PinNumber_2
#define PinNum4     GPIO_PinNumber_3

// PB3 >> OCR0 >>> PWM for all motors 

//		|------------------------------------------------------------------|
//		|=================Macros Configuration References==================|
//		|------------------------------------------------------------------|



//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|


/**================================================================
* @Fn -
* @brief -
* @param[in] -
* @param[out] -
* @retval -
* Note -
*/

void DC_Motor_Init(struct GPIO_t * GPIOx , uint8_t PinForward , uint8_t PinBackward );

void DC_Motor_Control(uint8_t direction , uint16_t DutyCycle);




#endif /* DC_MOTOR_H_ */