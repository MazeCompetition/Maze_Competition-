/*
 * TIMERs.c
 *
 * Created: 3/3/2023 3:12:51 PM
 *  Author: Bishoy Refaat
 */ 

//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|
#include "TIMERs.h"


//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|


//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|


//		|-----------------------------------------------|
//		|=============GENERIC FUNCTIONS=================|
//		|-----------------------------------------------|
void (*GP_TIMER0_OverFlow)(void);
void (*GP_TIMER0_Compare_Match)(void);

void (*GP_TICIE1_InputCapture)(void);
void (*GP_OCIE1A_Compare_MatchA)(void);
void (*GP_TOIE1_OverFlow)(void);
void (*GP_OCIE1B_Compare_MatchB)(void);

void (*GP_TOIE2_OverFlow)(void);
void (*GP_OCIE2_Compare_Match)(void);


//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|


//			 |\__________		Timer 0		__________/|
//			 |\_______________________________________/|
void MCAL_TIMER0_INIT(TIMER0_CFG_t * timcfg)
{
	MCAL_TIMER0_GPIO_SetPINS();

	TIM0 * TIM ;
	if(timcfg->INT0_EN != INT0_EN_Disable)
	{
		General_Interrupt_EN;
		GP_TIMER0_Compare_Match = timcfg->P_OCIE0;
		GP_TIMER0_OverFlow = timcfg->P_TOIE0;
		//TIMCOM->TIMSK0 = (TIMCOM->TIMSK0 & ~(0b11)) | timcfg->INT0_EN;
		*((volatile uint8_t * )0x59) |= 1;  
	}
	
	OCR0 = timcfg->OutCR0;	//0x0F
	Timer0->TCCR0  |= (1 << 5) ;		// 
	Timer0->TCCR0 |=  (1 << 2);			//101
	Timer0->TCCR0 |= (1<<6);	//	1 << 6
	Timer0->TCNT0 |= timcfg->TCNT0;		//0
	
		
	
}

void MCAL_TIMER0_GPIO_SetPINS(void)
{
	//OC0 -> PB3
	struct GPIO_CFG_t gpiocfg;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_3;
	MCAL_GPIO_INIT_PIN(PORTB , &gpiocfg);
}




//			 |\__________		Timer 1		__________/|
//			 |\_______________________________________/|

void MCAL_TIMER1_INIT(TIMER1_CFG_t * timcfg)
{
	if (timcfg->INT1_EN != INT1_EN_Disable)
	{
		General_Interrupt_EN;
		GP_TICIE1_InputCapture = timcfg->P_TICIE1;
		GP_OCIE1A_Compare_MatchA = timcfg->P_OCIE1A;
		GP_TOIE1_OverFlow = timcfg->P_TICIE1;
		GP_OCIE1B_Compare_MatchB = timcfg->P_OCIE1B;
		TIMCOM->TIMSK = (TIMCOM->TIMSK & ~(0b1111 << 2)) | timcfg->INT1_EN;
	}
	Timer1->TCCR1A = (Timer1->TCCR1A & ~(3 << 6)) | timcfg->COM1A;
	
	Timer1->TCCR1A = (Timer1->TCCR1A & ~(3 << 4)) | timcfg->COM1B;


	Timer1->TCCR1B = (Timer1->TCCR1B & ~(1 << 7)) | timcfg->ICNC1;
	
	Timer1->TCCR1B = (Timer1->TCCR1B & ~(1 << 6)) | timcfg->ICES1;

	Timer1->TCCR1B = (Timer1->TCCR1B & ~(7 << 0)) | timcfg->CS1;

	Timer1->TCNT1H = timcfg->TCNT1H;
	Timer1->TCNT1L = timcfg->TCNT1L;
	
	Timer1->OCR1AH = timcfg->OCR1AH;
	Timer1->OCR1AL = timcfg->OCR1AL;
	
	Timer1->OCR1BH = timcfg->OCR1BH;
	Timer1->OCR1BL = timcfg->OCR1BL;
	
// 	Timer1->ICR1H = timcfg->ICR1H;
// 	Timer1->ICR1L = timcfg->ICR1L;


	Timer1->TCCR1A = (Timer1->TCCR1A & ~(3 << 0)) | (timcfg->WGM1 & 3);
	Timer1->TCCR1B = (Timer1->TCCR1B & ~(3 << 3)) | (((timcfg->WGM1 >> 2) & 3) << 3);

	MCAL_TIMER1_GPIO_SetPINS();
}


void MCAL_TIMER1_GPIO_SetPINS()
{
	//OC1A -> PD5
	struct GPIO_CFG_t gpiocfg;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_5;
	MCAL_GPIO_INIT_PIN(PORTD , &gpiocfg);
	
	//OC1B -> PD4
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_4;
	MCAL_GPIO_INIT_PIN(PORTD , &gpiocfg);	
	
	//ICP1 -> PD6
	gpiocfg.GPIO_Mode = GPIO_Mode_INPUT;
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_6;
	MCAL_GPIO_INIT_PIN(PORTD , &gpiocfg);	
}


                                
//			 |\__________		Timer 2		__________/|
//			 |\_______________________________________/|

void MCAL_TIMER2_INIT(TIMER2_CFG_t * timcfg)
{
	if (timcfg->INT2_EN != INT2_EN_Disable)
	{
		General_Interrupt_EN;
		TIMCOM->TIMSK = (TIMCOM->TIMSK & (3 << 6)) | timcfg->INT2_EN;
		GP_TOIE2_OverFlow = timcfg->P_TOIE2;
		GP_OCIE2_Compare_Match = timcfg->P_OCIE2;	
	}
	
	Timer2->TCCR2 = (Timer2->TCCR2 & ~((1 << 6)|(1 << 3))) | timcfg->WGM2;
	
	Timer2->TCCR2 = (Timer2->TCCR2 & ~((1 << 4) | (1 << 5))) | timcfg->COM2;
	
	Timer2->TCCR2 = (Timer2->TCCR2 & ~(7 << 0)) | timcfg->CS2;
	
	Timer2->TCNT2 = timcfg->TCNT0;
	
	Timer2->OCR2 = timcfg->OCR2;
	
	Timer2->ASSR = (Timer2->ASSR & ~(1 << 3)) | timcfg->AS2;
	
	MCAL_TIMER2_GPIO_SetPINS();
}


void MCAL_TIMER2_GPIO_SetPINS(void)
{
	
	//OC2 -> PD7
	struct GPIO_CFG_t gpiocfg;
	gpiocfg.GPIO_Mode = GPIO_Mode_OUTPUT;
	gpiocfg.GPIO_PinNumber = GPIO_PinNumber_7;
	MCAL_GPIO_INIT_PIN(PORTD , &gpiocfg);
	
	
}








//			 |\__________		Timer 0		__________/|
//			 |\_______________________________________/|


void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	GP_TIMER0_OverFlow();
}


void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	GP_TIMER0_Compare_Match();
}



//			 |\__________		Timer 2		__________/|
//			 |\_______________________________________/|

void __vector_5 (void) __attribute__((signal));
void __vector_5 (void)
{
	GP_TOIE2_OverFlow();
}

void __vector_4 (void) __attribute__((signal));
void __vector_4 (void)
{
	GP_OCIE2_Compare_Match();
}




//			 |\__________		Timer 1		__________/|
//			 |\_______________________________________/|

void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	GP_TICIE1_InputCapture();

}


void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	GP_OCIE1A_Compare_MatchA();
}



void __vector_8 (void) __attribute__((signal));
void __vector_8 (void)
{
	GP_OCIE1B_Compare_MatchB();

}


void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	GP_TOIE1_OverFlow();
}












