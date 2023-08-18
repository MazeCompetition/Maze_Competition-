/*
 * DC_Motor.c
 *
 * Created: 8/14/2023 11:14:42 AM
 *  Author: Bishoy Refaat
 */ 



//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|

#include "DC_Motor.h"

//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|


//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|




//		|------------------------------------------------------------------|
//		|=================Macros Configuration References==================|
//		|------------------------------------------------------------------|



//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|



void DC_Motor_Init(struct GPIO_t * GPIOx , uint8_t PinForward , uint8_t PinBackward )
{
	TIMER0_CFG_t DC_Motor_cfg;
	DC_Motor_cfg.COM0 = COM0_Clear;
	DC_Motor_cfg.CS0 = CS0_256;
	DC_Motor_cfg.INT0_EN = INT0_EN_Disable;
	DC_Motor_cfg.OutCR0 = 0;
	DC_Motor_cfg.P_OCIE0 = NULL;
	DC_Motor_cfg.P_TOIE0 = NULL;
	DC_Motor_cfg.TCNT0 = 0x00;
	DC_Motor_cfg.TIMNUM = TIMNUM_0;
	DC_Motor_cfg.WGM0 = WGM0_PhaseCorrect;
	
	MCAL_TIMER0_INIT(&DC_Motor_cfg);
	
	struct GPIO_CFG_t gpio_cfg;
	gpio_cfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpio_cfg.GPIO_PinNumber = PinForward;
	MCAL_GPIO_INIT_PIN(GPIOx , &gpio_cfg);

	gpio_cfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpio_cfg.GPIO_PinNumber = PinBackward;
	MCAL_GPIO_INIT_PIN(GPIOx , &gpio_cfg);

	
}

void DC_Motor_Control( uint8_t direction , uint16_t DutyCycle)
{
	

	Timer0->TCCR0 |=  (1 << 2);

 	OCR0 = (uint8_t)(( (float)DutyCycle /100) * 256);	//0x0F

	
	if(direction == direction_right)
	{
		
		MCAL_GPIO_WRITE_PIN(PORTx , PinNum1 , 1);
		MCAL_GPIO_WRITE_PIN(PORTx , PinNum2 , 0);
		
	}
	else 
	{
			MCAL_GPIO_WRITE_PIN(PORTx , PinNum1 , 0);
			MCAL_GPIO_WRITE_PIN(PORTx , PinNum2 , 1);
	}	
}
void DC_Motor_Stop(void)
{	
	
	Timer0->TCNT0 &= ~(7);
	OCR0 = 0 ;
}
