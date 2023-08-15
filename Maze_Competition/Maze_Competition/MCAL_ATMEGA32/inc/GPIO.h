/*
 * GPIO.h
 *
 * Created: 2/6/2023 4:18:32 PM
 *  Author: Bishoy Refaat
 */ 


#ifndef _GPIO_H_
#define _GPIO_H_

//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|
#include "ATMEGA32.h"



//		|-----------------------------------------------|
//		|======User Type Definitions (structures)=======|
//		|-----------------------------------------------|
struct GPIO_CFG_t {
	unsigned char GPIO_PinNumber;		//Specifies the number bit number used
										//Configurations @ref GPIO_PinNumber_define
						
	unsigned char GPIO_Mode;		//Specifies the mode of the pin
									//Configurations @ref GPIO_Mode_define
};
	



//		|------------------------------------------------------------------|
//		|=================Macros Configuration References==================|
//		|------------------------------------------------------------------|


		//***********************@ref GPIO_PinNumber_define***********************
#define GPIO_PinNumber_0	0
#define GPIO_PinNumber_1	1
#define GPIO_PinNumber_2	2
#define GPIO_PinNumber_3	3
#define GPIO_PinNumber_4	4
#define GPIO_PinNumber_5	5
#define GPIO_PinNumber_6	6
#define GPIO_PinNumber_7	7

		//***********************@ref GPIO_Mode_define***********************
#define GPIO_Mode_INPUT		0
#define GPIO_Mode_INPUT_FLO 2
#define GPIO_Mode_OUTPUT	1		
		
//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|



/**================================================================
* @Fn - MCAL_GPIO_INIT
* @brief - Initialize the portx
* @param[in] - GPIO port
* @param[out] - GPIO pin in the specific port (in the last parameter)
*               takes values @ref GPIO_PinNumber  @ref GPIO_MODE  @ref GPIO_FREQ
*/
void MCAL_GPIO_INIT_PIN(struct GPIO_t* PORTx , struct GPIO_CFG_t* PIN);
//void MCAL_GPIO_INIT_PORT(struct GPIO_t * GPIOx ,GPIO_PortConfig_t *PORT_CONFIG);



/**================================================================
* @Fn - MCAL_GPIO_RESET
* @brief - PORT needed to be reset -> takes values included GENERIC MACROS  GPIO_RESET section in GPIO header
* @param[in] - portx
*/
void MCAL_GPIO_RESET(struct GPIO_t* PORTx_RESET);



/**================================================================
* @Fn - MCAL_GPIO_READ_PIN
* @brief - Read a pin from portx
* @param[in] - portx
* @param[out] - Pin number in portx (the first parameter)
* @retval- 8 bit return value read from the pin (the second parameter)
*/
unsigned char MCAL_GPIO_READ_PIN(struct GPIO_t* PORTx , unsigned char PIN_NUMBER);



/**================================================================
* @Fn - MCAL_GPIO_READ_PORT
* @brief - Read the whole port
* @param[in] - portx
* @retval- 16 bit value read from portx
*/
unsigned char MCAL_GPIO_READ_PORT( struct GPIO_t * PORTx);



/**================================================================
* @Fn - MCAL_GPIO_WRITE_PIN
* @brief - Write a value in a specific pin portx
* @param[in] - portx
* @param[in] - number of a specific pint in portx
* @param[out] - 8 bit value Written to pinx in portx
*/
void MCAL_GPIO_WRITE_PIN(struct GPIO_t * PORTx , unsigned char PIN_NUMBER , unsigned char VAL);



/**================================================================
* @Fn - MCAL_GPIO_WRITE_PORT
* @brief - Write a value in the whole port
* @param[in] - portx
* @param[out] - 8 bit value Written to portx
*/
void MCAL_GPIO_WRITE_PORT(struct GPIO_t* PORTx , unsigned char VAL);



/**================================================================
* @Fn - MCAL_struct GPIO_tOGGLE_PIN
* @brief - toggle a specific pin
* @param[in] - portx
* @param[in] - pin number
*/
void MCAL_GPIO_TOGGLE_PIN(struct GPIO_t* PORTx , unsigned char PIN_NUMBER);



#endif