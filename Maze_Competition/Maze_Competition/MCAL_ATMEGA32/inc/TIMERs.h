/*
 * TIMERs.h
 *
 * Created: 3/3/2023 3:13:46 PM
 *  Author: Bishoy Refaat
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|
#include "ATMEGA32.h"
#include "GPIO.h"



//		|-----------------------------------------------|
//		|================GENERIC MACROS=================|
//		|-----------------------------------------------|

		
//		|-----------------------------------------------|
//		|=============GENERIC VARIABLES=================|
//		|-----------------------------------------------|


//		|-----------------------------------------------|
//		|=============GENERIC FUNCTIONS=================|
//		|-----------------------------------------------|




//		|-----------------------------------------------|
//		|======User Type Definitions (structures)=======|
//		|-----------------------------------------------|
typedef struct  
{
	uint8_t TIMNUM;		//Specifies the timer number used
						//Specified @ref TIMNUM_define
				
	uint8_t WGM0;		//Specifies the waveform used
						//Specified @ref WGM0_define
			
	uint8_t FOC0;		
						
	uint8_t COM0;		//Specifies Compare Match Output Mode
						//Specified @ref COM0_define
	
	uint8_t CS0;		//Specifies the clock select (prescaler)
						//Specified @ref CS0_define
	
	uint8_t TCNT0;		//Specifies the timer value
						//Specified @ref TCNT0_define
	
	uint8_t OutCR0;		//Specifies the compare value
						//Specified @ref OCR0_define
						
	uint8_t INT0_EN ;   //@ref INT0_EN_define	
	
	void (*P_TOIE0)(void);	//Timer/CounterTimer/Counter0 Overflow Interrupt Enable
	void (*P_OCIE0)(void);	//Timer/CounterTimer/Counter0 Output Compare Match Interrupt Enable		

}TIMER0_CFG_t;


typedef struct
{
	uint8_t TIMNUM;		//Specifies the timer number used
						//Specified @ref TIMNUM_define
	uint8_t FOC1A;
	
	uint8_t FOC1B;
	
	uint8_t ICNC1;		//Input Capture Noise Canceler
						//Specified @ref ICNC1_define
						
	uint8_t ICES1;		//Input Capture Edge Select
						//Specified @ref ICES1_define
						
						
	uint8_t ICR1L;		//Input Capture Register 1 Low byte
						//Specified @ref ICR1L_define
	
	uint8_t ICR1H;		//Input Capture Register 1 High byte
						//Specified @ref ICR1H_define
	
	uint8_t WGM1;		//Specifies the waveform used
						//Specified @ref WGM1_define
	
	uint8_t COM1A;		//Specifies Compare Match Output Mode
						//Specified @ref COM1A_define
						
	uint8_t COM1B;		//Specifies Compare Match Output Mode
						//Specified @ref COM1B_define					
	
	uint8_t CS1;		//Specifies the clock select (prescaler)
						//Specified @ref CS1_define
	
	uint8_t TCNT1L;		//Specifies the timer value
						//Specified @ref TCNT1L_define
						
	uint8_t TCNT1H;		//Specifies the timer value
						//Specified @ref TCNT1H_define
	
	uint8_t OCR1AL;		//Specifies the compare value
						//Specified @ref OCR1AL_define
	
	uint8_t OCR1AH;		//Specifies the compare value
						//Specified @ref OCR1AH_define
	
	uint8_t OCR1BL;		//Specifies the compare value
						//Specified @ref OCR1BL_define

	uint8_t OCR1BH;		//Specifies the compare value
						//Specified @ref OCR1BL_define	
											
	uint8_t INT1_EN ;   //@ref INT1_EN_define
	
	void (*P_TICIE1)(void);	//Timer/Counter1, Input Capture Interrupt Enable
	void (*P_OCIE1A)(void);	//Timer/Counter1, Output Compare A Match Interrupt Enable
	void (*P_OCIE1B)(void);	//Timer/Counter1, Output Compare B Match Interrupt Enable
	void (*P_TOIE1)(void);	//Timer/Counter1, Overflow Interrupt Enable
}TIMER1_CFG_t;



typedef struct
{
	uint8_t TIMNUM;		//Specifies the timer number used
						//Specified @ref TIMNUM_define
	
	uint8_t FOC2;
	
	uint8_t WGM2;		//Specifies the waveform used
						//Specified @ref WGM2_define
	
	uint8_t COM2;		//Specifies Compare Match Output Mode
						//Specified @ref COM2_define
	
	uint8_t CS2;		//Specifies the clock select (prescaler)
						//Specified @ref CS2_define
	
	uint8_t TCNT0;		//Specifies the timer value
						//Specified @ref TCNT0_define
	
	uint8_t OCR2;		//Specifies the compare value
						//Specified @ref OCR0_define
	
	uint8_t AS2;		//	Asynchronous Timer/Counter2
						//When AS2 is written to zero, Timer/Counter 2 is clocked from the I/O clock, clkI/O.
						//When AS2 is written to one, Timer/Counter 2 is clocked from a crystal Oscillator connected to the Timer Oscillator 1 (TOSC1) pin
						//Specified @ref AS2_define
				
	uint8_t PSR2;		//Prescaler Reset Timer/Counter2
						//Specified @ref PSR2_define
	
	
	uint8_t INT2_EN ;   //@ref INT2_EN_define
	
	void (*P_TOIE2)(void);	//Timer/CounterTimer/Counter0 Overflow Interrupt Enable
	void (*P_OCIE2)(void);	//Timer/CounterTimer/Counter0 Output Compare Match Interrupt Enable

}TIMER2_CFG_t;

//		|------------------------------------------------------------------|
//		|=================Macros Configuration References==================|
//		|------------------------------------------------------------------|

 

//***********************@ref TIMNUM_define***********************

#define TIMNUM_0		0
#define TIMNUM_1		1
#define TIMNUM_2		2




//			 |\__________		Timer 0		__________/| 
//			 |\_______________________________________/|

//***********************@ref WGM0_define***********************
#define WGM0_Normal			0
#define WGM0_FastPWM		(1 << 6)|(1 << 3)
#define WGM0_PhaseCorrect	(1 << 6)
#define WGM0_CTC			(1 << 3)	//Clear Timer on Compare Match (CTC) Mode



//***********************@ref COM0_define***********************

#define COM0_NormalOperationPort	0

#define COM0_Toggle					(1 << 4)	//Toggle OC0 on Compare Match not used in PWM & Phase correct

#define COM0_Clear					(1 << 5)	//Clear OC0 on Compare Match & set OC0 at BOTTOM on PWM 
												//Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when downcounting. on Phase correct

#define COM0_Set				(1 << 4) | (1 << 5)	//Set OC0 on Compare Match
													//Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when downcounting on Phase correct


//***********************@ref CS0_define***********************

#define CS0_NoCLK			0b000
#define CS0_NoPrescal		0b001
#define CS0_8				0b010
#define CS0_64				0b011
#define CS0_256				0b100
#define CS0_1024			0b101
#define CS0_EXTCLK_FallingEdg0	0b110
#define CS0_EXTCLK_FallingEdg1	0b111


//***********************@ref INT0_EN_define	***********************
#define INT0_EN_Disable		 0 
#define INT0_EN_TOIE0		0b01	//Timer/CounterTimer/Counter0 Overflow Interrupt Enable
#define INT0_EN_OCIE0		0b10	//Timer/CounterTimer/Counter0 Output Compare Match Interrupt Enable
#define INT0_EN_TOIE0_OCIE0	0b11


//***********************@ref OCR0_define***********************





//			 |\__________		Timer 1		__________/| 
//			 |\_______________________________________/|


//***********************@ref ICNC1_define***********************
#define ICNC1_Enable		(1 << 7)
#define ICNC1_Disable		0


//***********************@ref ICES1_define***********************
#define ICES1_FallingEdge		0
#define ICES1_RisingEdge		(1 << 6)



//***********************@ref WGM1_define***********************
//			Mode				VAL				TOP			OCR1x UPDATE	TOV1 SET VAL
#define WGM1_Normal				0			//	0xFFFF		 Immediate			MAX
#define WGM1_PWM_PhC_8BIT		0b0001		//	0x00FF			TOP				BOTTOM
#define WGM1_PWM_PhC_9BIT		0b0010		//	0x01FF			TOP				BOTTOM
#define WGM1_PWM_PhC_10BIT		0b0011		//	0x03FF			TOP				BOTTOM
#define WGM1_CTC0				0b0100		//	OCR1A		Immediate			MAX
#define WGM1_FastPWM_8BIT		0b0101		//	0x00FF			BOTTOM			TOP
#define WGM1_FastPWM_9BIT		0b0110		//	0x01FF			BOTTOM			TOP
#define WGM1_FastPWM_10BIT		0b0111		//	0x03FF			BOTTOM			TOP
#define WGM1_PWM_PhC_FreqC0		0b1000		//	ICR1			BOTTOM			BOTTOM
#define WGM1_PWM_PhC_FreqC1		0b1001		//	OCR1A			BOTTOM			BOTTOM
#define WGM1_PWM_PhC0			0b1010		//	ICR1			TOP				BOTTOM
#define WGM1_PWM_PhC1			0b1011		//	OCR1A			TOP				BOTTOM
#define WGM1_CTC1				0b1100		//	ICR1		Immediate			MAX
#define WGM1_FastPWM0			0b1110		//	ICR1			BOTTOM			TOP
#define WGM1_FastPWM1			0b1111		//	OCR1A			BOTTOM			TOP
				



//***********************@ref COM1A_define***********************

#define COM1A_NormalOperationPort	0		//Normal port operation, OC1A/OC1B disconnected

#define COM1A_Toggle					(1 << 6)	//Toggle OC1A/OC1B on Compare Match.
													//Fast PWM -> WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation). For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected
													//Phase correct -> WGM13:0 = 9 or 14: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation). For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected.
													
#define COM1A_Clear					(1 << 7)	//Clear OC1A/OC1B on Compare Match (Set output to low level).
												//Fast PWM -> Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM (non-inverting mode)
												//Phase correct -> Clear OC1A/OC1B on Compare Match when up-counting. Set OC1A/OC1B on Compare Match when down-counting

#define COM1A_Set				(1 << 7) | (1 << 6)	//Set OC0 on Compare Match
													//Fast PWM -> Set OC1A/OC1B on Compare Match, clear OC1A/OC1B at BOTTOM (inverting mode)
													//Phase correct -> Set OC1A/OC1B on Compare Match when up-counting. Clear OC1A/OC1B on Compare Match when down-counting

//***********************@ref COM1B_define***********************

#define COM1B_NormalOperationPort	0

#define COM1B_Toggle					(1 << 4)	//Toggle OC1A/OC1B on Compare Match.
													//Fast PWM -> WGM13:0 = 15: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation). For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected
													//Phase correct -> WGM13:0 = 9 or 14: Toggle OC1A on Compare Match, OC1B disconnected (normal port operation). For all other WGM1 settings, normal port operation, OC1A/OC1B disconnected.

#define COM1B_Clear					(1 << 5)	//Clear OC1A/OC1B on Compare Match (Set output to low level).
												//Fast PWM -> Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM (non-inverting mode)
												//Phase correct -> Clear OC1A/OC1B on Compare Match when up-counting. Set OC1A/OC1B on Compare Match when down-counting

#define COM1B_Set				(1 << 4) | (1 << 5)	//Set OC0 on Compare Match
													//Fast PWM -> Set OC1A/OC1B on Compare Match, clear OC1A/OC1B at BOTTOM (inverting mode)
													//Phase correct -> Set OC1A/OC1B on Compare Match when up-counting. Clear OC1A/OC1B on Compare Match when down-counting



//***********************@ref CS1_define***********************

#define CS1_NoCLK			0b000
#define CS1_NoPrescal		0b001
#define CS1_8				0b010
#define CS1_64				0b011
#define CS1_256				0b100
#define CS1_1024			0b101
#define CS1_EXTCLK_FallingEdg0	0b110
#define CS1_EXTCLK_FallingEdg1	0b111


//***********************@ref INT1_EN_define***********************
#define INT1_EN_Disable					 0 
#define INT1_EN_TICIE1					(1 << 5)	//Timer/CounterTimer/Counter0 Overflow Interrupt Enable
#define INT1_EN_OCIE1A					(1 << 4)	//Timer/CounterTimer/Counter0 Output Compare Match Interrupt Enable
#define INT1_EN_OCIE1B					(1 << 3)
#define INT1_EN_TOIE1					(1 << 2)
#define INT1_EN_TOIE1_OCIE1A			(0b0101 << 2)
#define INT1_EN_TICIE1_OCIE1A			(0b1100 << 2)
#define INT1_EN_TOIE1_OCIE1B			(0b0011 << 2)
#define INT1_EN_TICIE1_OCIE1B			(0b1010 << 2)
#define INT1_EN_TOIE1_TICIE1_OCIE1A		(0b1101 << 2)
#define INT1_EN_TOIE1_TICIE1_OCIE1B		(0b1011 << 2)



//			 |\__________		Timer 2		__________/| 
//			 |\_______________________________________/|

//***********************@ref WGM2_define***********************
//			Mode				VAL					TOP			OCR1x UPDATE	TOV1 SET VAL
#define WGM2_Normal			0					//	0xFF		Immediate			MAX
#define WGM2_FastPWM		(1 << 6)|(1 << 3)	//	0xFF			BOTTOM			MAX
#define WGM2_PWM_PhC		(1 << 6)			//	0xFF			TOP				BOTTOM
#define WGM2_CTC			(1 << 3)			//	OCR2		Immediate			MAX			
//Clear Timer on Compare Match (CTC) Mode


//***********************@ref COM2_define***********************

#define COM2_NormalOperationPort	0

#define COM2_Toggle					(1 << 4)	//Toggle OC0 on Compare Match not used in PWM & Phase correct

#define COM2_Clear					(1 << 5)	//Clear OC0 on Compare Match & set OC0 at BOTTOM on PWM 
												//Clear OC0 on Compare Match when up-counting. Set OC0 on Compare Match when downcounting. on Phase correct

#define COM2_Set				(1 << 4) | (1 << 5)	//Set OC0 on Compare Match
													//Set OC0 on Compare Match when up-counting. Clear OC0 on Compare Match when downcounting on Phase correct


//***********************@ref CS2_define***********************

#define CS2_NoCLK			0b000
#define CS2_NoPrescal		0b001
#define CS2_8				0b010
#define CS2_32				0b011
#define CS2_64				0b100
#define CS2_128				0b101
#define CS2_256				0b110
#define CS2_1024			0b111



//***********************@ref INT2_EN_define***********************
#define INT2_EN_Disable		 0 
#define INT2_EN_TOIE2		(0b01 << 6)	//Timer/CounterTimer/Counter0 Overflow Interrupt Enable
#define INT2_EN_OCIE2		(0b10 << 6)	//Timer/CounterTimer/Counter0 Output Compare Match Interrupt Enable
#define INT2_EN_TOIE2_OCIE2	(0b11 << 6)


//***********************@ref AS2_define***********************
#define AS2_IOCLK		0
#define AS2_CRYS		(1 << 3)

//***********************@ref PSR2_define***********************

//		|------------------------------------------------------------------|
//		|=============APIs Supported by "MCAL GPIO DRIVER"=================|
//		|------------------------------------------------------------------|


//			 |\__________		Timer 0		__________/|
//			 |\_______________________________________/|

void MCAL_TIMER0_INIT(TIMER0_CFG_t * timcfg);
void MCAL_TIMER0_GPIO_SetPINS(void);

//			 |\__________		Timer 1		__________/|
//			 |\_______________________________________/|
void MCAL_TIMER1_INIT(TIMER1_CFG_t * timcfg);
void MCAL_TIMER1_GPIO_SetPINS(void);

//			 |\__________		Timer 2		__________/|
//			 |\_______________________________________/|
void MCAL_TIMER2_INIT(TIMER2_CFG_t * timcfg);
void MCAL_TIMER2_GPIO_SetPINS(void);


/**================================================================
* @Fn -
* @brief -
* @param[in] -
* @param[out] -
* @retval -
* Note -
*/




#endif /* TIMERS_H_ */