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


#define Motor_Enable_PORT            PORTB

// Front Right Motor 
#define Motor_Right               1 
#define Motor_Right_1          GPIO_PinNumber_0
#define Motor_Right_2          GPIO_PinNumber_1

// Front Left Motor 
#define Motor_Left                 2
#define Motor_Left_1           GPIO_PinNumber_2
#define Motor_Left_2           GPIO_PinNumber_4



// PB3 >> OCR0 >>> PWM for all motors 

#define Motor_PWM_Port               PORTB
#define Motor_PWM_Pin                GPIO_PinNumber_3

#define  RESET_PIN                   0
#define  SET_PIN                     1
//		|------------------------------------------------------------------|
//		|=================Macros Configuration References==================|
//		|------------------------------------------------------------------|


/**================================================================
* @Fn -
* @brief -
* @param[in] -
* @param[out] -
* @retval -
* Note -
*/

void DC_Motors_Init();

void DC_Motor_Control( uint8_t Motor, uint8_t direction , uint8_t DutyCycle );

void Car_MoveTo_Right(void);

void Car_MoveTo_Left(void);

void Car_MoveTo_Forward(void);

void Car_MoveTo_Backward(void);

void Car_MoveTo(uint8_t Direction);

void Car_Stop(void);


#endif /* DC_MOTOR_H_ */