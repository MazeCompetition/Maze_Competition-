/*
 * Ultrasonic.h
 *
 * Created: 8/14/2023 10:53:04 AM
 *  Author: Bishoy Refaat
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_






//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|

#include "ATMEGA32.h"
#include "GPIO.h"
#include "TIMERs.h"

//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|

#define US_PORTx      PORTD
#define Trig1      GPIO_PinNumber_0
#define Trig2      GPIO_PinNumber_1
#define Trig3      GPIO_PinNumber_2
#define Trig4      GPIO_PinNumber_3



#define  Right         0
#define  Left          1
#define  Front         2


//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|



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

void Ultrasonic_Init();

uint16_t Ultrasonic_Read(uint8_t UltNum);


#endif /* ULTRASONIC_H_ */