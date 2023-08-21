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



void DC_Motors_Init( )
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
	gpio_cfg.GPIO_PinNumber = Motor_Right_1;
	MCAL_GPIO_INIT_PIN(Motor_Enable_PORT , &gpio_cfg);

	gpio_cfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpio_cfg.GPIO_PinNumber = Motor_Right_2;
	MCAL_GPIO_INIT_PIN(Motor_Enable_PORT , &gpio_cfg);
	
	gpio_cfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpio_cfg.GPIO_PinNumber = Motor_Left_1;
	MCAL_GPIO_INIT_PIN(Motor_Enable_PORT , &gpio_cfg);

	gpio_cfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpio_cfg.GPIO_PinNumber = Motor_Left_2;
	MCAL_GPIO_INIT_PIN(Motor_Enable_PORT , &gpio_cfg);
		
	
	gpio_cfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpio_cfg.GPIO_PinNumber = Motor_PWM_Pin;
	MCAL_GPIO_INIT_PIN(Motor_PWM_Port , &gpio_cfg);
	
	Car_Stop();
	
	
}

void DC_Motor_Control( uint8_t Motor, uint8_t direction , uint8_t DutyCycle )
{
	

	Timer0->TCCR0 |=  (1 << 2);

 	OCR0 = (uint8_t)(( (float)DutyCycle /100) * 256);	//0x0F

	if(Motor == Motor_Right)
	{
		if(direction == direction_right)
		{
			
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT,  Motor_Right_1 , SET_PIN);
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Right_2 , RESET_PIN);
			
		}
		else
		{
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Right_1 , RESET_PIN);
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Right_2 , SET_PIN);
		}
		
	}
	else if (Motor == Motor_Left)
	{
		if(direction == direction_right)
		{
			
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT,  Motor_Left_1 , SET_PIN);
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Left_2 , RESET_PIN);
			
		}
		else
		{
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Left_1 , RESET_PIN);
			MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Left_2 , SET_PIN);
		}
		
	}
	
		
	}

}

void Car_MoveTo_Right(void)
{
	
	// Right ......> Forward 
	// Left .......> Backword 
	
	DC_Motor_Control(Motor_Right,direction_left,50);
	DC_Motor_Control(Motor_Right,direction_left,50);
	
	DC_Motor_Control(Motor_Left,direction_right,50);
	DC_Motor_Control(Motor_Left,direction_right,50);
	
	_delay_ms(5);
	Car_Stop();	
}

void Car_MoveTo_Left(void)
{
	// Right ......> Forward
	// Left .......> Backword
		
	DC_Motor_Control(Motor_Right,direction_right,50);
	DC_Motor_Control(Motor_Right,direction_right,50);
		
	DC_Motor_Control(Motor_Left,direction_left,50);
	DC_Motor_Control(Motor_Left,direction_left,50);
		
	_delay_ms(5);
	Car_Stop();	
}

void Car_MoveTo_Forward(void)
{
	
	// Right ......> Forward
	// Left .......> Backword
		
	DC_Motor_Control(Motor_Right,direction_right,50);
	DC_Motor_Control(Motor_Right,direction_right,50);
		
	DC_Motor_Control(Motor_Left,direction_right,50);
	DC_Motor_Control(Motor_Left,direction_right,50);
		
	_delay_ms(5);
	Car_Stop();
	
}

void Car_MoveTo_Backward(void)
{
	// Right ......> Forward
	// Left .......> Backword
	
	DC_Motor_Control(Motor_Right,direction_left,50);
	DC_Motor_Control(Motor_Right,direction_left,50);
	
	DC_Motor_Control(Motor_Left,direction_right,50);
	DC_Motor_Control(Motor_Left,direction_right,50);
	
	_delay_ms(10);	
	Car_Stop();
	
}

void Car_MoveTo(uint8_t Direction)
{
	if (Direction == 'F')
	{
		Car_MoveTo_Forward();
	}
	else if (Direction == 'B')
	{
		Car_MoveTo_Backward();
	}
	else if (Direction == 'R')
	{
		Car_MoveTo_Right();
	}
	else if (Direction == 'L')
	{
		Car_MoveTo_Left();
	}
}

void Car_Stop(void)
{
	
	Timer0->TCNT0 &= ~(7);
	OCR0 = 0 ;
	
	MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Right_1,RESET_PIN);
	MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Right_2,RESET_PIN);
	
	MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Left_1,RESET_PIN);
	MCAL_GPIO_WRITE_PIN(Motor_Enable_PORT , Motor_Left_2,RESET_PIN);

}