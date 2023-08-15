/*
 * DRIVERS.c
 *
 * Created: 2/6/2023 4:11:34 PM
 * Author : Bishoy Refaat
 */ 

#include "ATMEGA32.h"
#include "GPIO.h"
#include "LCD_DRIVER.h"
#include "TIMERs.h"
#include "DC_Motor.h"
#include "Ultrasonic.h"





void LCDInit()
{
	struct GPIO_CFG_t gpiocfg;
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_1;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_2;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_3;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);
	
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_4;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);			

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_5;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);

	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_6;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	MCAL_GPIO_INIT_PIN(PORTA , &gpiocfg);
	
	LCD_INIT();
}




int main(void)
{
	
	LCDInit();
	DC_Motor_Init(PORTB , GPIO_PinNumber_4 , GPIO_PinNumber_5 );
Ultrasonic_Init(PORTD , GPIO_PinNumber_0 , GPIO_PinNumber_1,GPIO_PinNumber_2,GPIO_PinNumber_3);


	float mmm;
	while (1)
	{
if((Ultrasonic_Read(1) < 60)|| (Ultrasonic_Read(2)< 60) || (Ultrasonic_Read(3)< 60) || (Ultrasonic_Read(4)< 60))
{
DC_Motor_Control(PORTB , GPIO_PinNumber_4 , GPIO_PinNumber_5 , direction_right , 0);	
LCD_WRITE_STRING("Yes");
_delay_ms(2000);
LCD_WRITE_COMMAND(LCD_Clear_Display);

}
else
{
	
			DC_Motor_Control(PORTB , GPIO_PinNumber_4 , GPIO_PinNumber_5 , direction_right , 80);
		
}

	}
}
