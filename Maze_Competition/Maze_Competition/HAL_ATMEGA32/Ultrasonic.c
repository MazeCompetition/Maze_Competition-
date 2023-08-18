/*
 * Ultrasonic.c
 *
 * Created: 8/14/2023 10:52:47 AM
 *  Author: Bishoy Refaat
 */ 




//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|
#include "Ultrasonic.h"


//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|


//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|



//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|


void Ultrasonic_Init()
{
	TIMER1_CFG_t ultrasonic;
	ultrasonic.TIMNUM = TIMNUM_1;	
	ultrasonic.ICNC1 = ICNC1_Disable;		
	ultrasonic.ICES1 = ICES1_RisingEdge;	
	ultrasonic.WGM1 = WGM1_Normal;
	ultrasonic.COM1A = 0;
	ultrasonic.COM1B = 0;
	ultrasonic.CS1 = CS1_1024;
	ultrasonic.TCNT1L = 0;
	ultrasonic.TCNT1H = 0;
	ultrasonic.OCR1AL = 0;
	ultrasonic.OCR1AH = 0;
	ultrasonic.OCR1BL = 0;
	ultrasonic.OCR1BH = 0;		
	ultrasonic.INT1_EN = INT1_EN_Disable;
	
	struct GPIO_CFG_t gpiocfg;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = Trig1;
	MCAL_GPIO_INIT_PIN(US_PORTx ,&gpiocfg );
	
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = Trig2;
	MCAL_GPIO_INIT_PIN(US_PORTx ,&gpiocfg );
			
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = Trig3;
	MCAL_GPIO_INIT_PIN(US_PORTx ,&gpiocfg );
				
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = Trig4;
	MCAL_GPIO_INIT_PIN(US_PORTx ,&gpiocfg );
		
	MCAL_TIMER1_INIT(&ultrasonic);
}

float Ultrasonic_Read(uint8_t UltNum)
{
	uint32_t Val = 0;
	float distance = 0;
	if (UltNum == 1)
	{
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig1 , 1);
		_delay_ms(10);
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig1 , 0);		
	}
	else if (UltNum == 2)
	{
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig2 , 1);
		_delay_ms(10);
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig2 , 0);
				
	}
	else if (UltNum == 3)
	{
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig3 , 1);
		_delay_ms(10);
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig3 , 0);
		
	}
	else if (UltNum == 4)
	{
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig4 , 1);
		_delay_ms(10);
		MCAL_GPIO_WRITE_PIN(US_PORTx , Trig4 , 0);
			
	}
	

	while(!(TIMCOM->TIFR &(1 << 5)));
	TIMCOM->TIFR |= (1 << 5);
	Timer1->TCNT1H = 0;
	Timer1->TCNT1L = 0;
	Timer1->TCCR1B = (Timer1->TCCR1B & ~(1 << 6)) | ICES1_FallingEdge;
	while(!(TIMCOM->TIFR &(1 << 5)));
	
	Val |= Timer1->ICR1L;
	Val |= (Timer1->ICR1H << 8);
	
	TIMCOM->TIFR |= (1 << 5);
	distance = (((float)Val/7812.5) * 343 / (float)2 ) * 100 ;
	
	Timer1->TCCR1B = (Timer1->TCCR1B & ~(1 << 6)) | ICES1_RisingEdge;
	return distance;	
}