/*
 * ATMEGA32.h
 *
 * Created: 2/6/2023 4:20:45 PM
 *  Author: Bishoy Refaat
 */ 


#ifndef ATMEGA32_H_
#define ATMEGA32_H_

//		|-----------------------------------------------|
//		|===================Includes====================|
//		|-----------------------------------------------|

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "util/delay.h"
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define DATA_ADRESS_BASE	0x0000
#define IO_Registers		0x0020
#define Internal_SRAM		0x0060





//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*
#define SREG	*((unsigned char *)(IO_Registers + 0x3F))	//The AVR status register

#define OSCCAL	(IO_Registers + 0x31)	//The Oscillator Calibration Register



				/*****************Memory Peripheral registers*****************/

#define EEARL	*((unsigned char *)(IO_Registers + 0x1E))	//The EEPROM Address Register Low
#define EEARH	*((unsigned char *)(IO_Registers + 0x1F))	//The EEPROM Address Register High
#define EEDR	*((unsigned char *)(IO_Registers + 0x1D))	//The EEPROM Data Register
#define EECR	*((unsigned char *)(IO_Registers + 0x1C))	//The EEPROM Control Register


					/*****************GPIO*****************/
#define SFIOR *((unsigned char *)(IO_Registers + 0x30))		//Special Function IO Register

struct GPIO_t 
{
	unsigned char PIN;
	unsigned char DDR;
	unsigned char PORT;
};


					/*****************EXTI*****************/
struct EXTI_t
{
	unsigned char MCUCSR;		//MCU Control and Status Register
	unsigned char MCUCR;		//MCU Control Register
	unsigned char RESEVED36;	//Don't touch
	unsigned char RESEVED37;	//Don't touch
	unsigned char RESEVED38;	//Don't touch
	unsigned char RESEVED39;	//Don't touch
	unsigned char GIFR;		//General Interrupt Flag Register
	unsigned char GICR;		//General Interrupt Control Register
};	


					/*****************USART*****************/				
typedef struct 
{
	uint8_t UBBRL;	//9	USART Baud Rate Register Low
	uint8_t UCSRB;	//A	USART Control and Status Register B
	uint8_t UCSRA;  //B	USART Control and Status Register A
	uint8_t UDR;	//C	USART I/O Data Register
		
}USART_t;

#define  UCSRC_UBBRH		*((uint8_t *)(IO_Registers + 0x20))	//20	USART Control and Status Register C	& USART Baud Rate Register High	
	
					/*****************SPI*****************/		
typedef struct
{
	uint8_t SPCR;	//0x0D SPI Control Register
	uint8_t SPSR;	//0x0E SPI Status Register
	uint8_t SPDR;	//0x0F SPI Data Register is a read/write register
}SPI_t;


					/*****************Timer*****************/
//Timer 0

#define OCR0		*((volatile uint8_t*)(0x5C))

typedef struct
{
	uint8_t TCNT0; 
	uint8_t TCCR0; 
}TIM0;


//Timer 1
typedef struct
{
	uint8_t ICR1L;
	uint8_t ICR1H;
	uint8_t OCR1BL;
	uint8_t OCR1BH;
	uint8_t OCR1AL;
	uint8_t OCR1AH;
	uint8_t TCNT1L;
	uint8_t TCNT1H;
	uint8_t TCCR1B;
	uint8_t TCCR1A;
}TIM1;

//Timer 2
typedef struct
{
	uint8_t ASSR;
	uint8_t OCR2;
	uint8_t TCNT2;
	uint8_t TCCR2;
}TIM2;



typedef struct
{
	uint8_t TIFR;
	uint8_t TIMSK;
}TIM012;




					/*****************ADC*****************/

typedef struct
{
	uint8_t ADCL;
	uint8_t ADCH;
	uint8_t ADCSRA;
	uint8_t ADMUX;
}ADC_t;
					

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*-
					/*****************GPIO*****************/
#define PORTA ((struct GPIO_t*)(IO_Registers + 0x19))
#define PORTB ((struct GPIO_t*)(IO_Registers + 0x16))
#define PORTC ((struct GPIO_t *)(IO_Registers + 0x13))
#define PORTD ((struct GPIO_t *)(IO_Registers + 0x10))

					/*****************EXTI*****************/
#define EXTI ((struct EXTI_t *)(IO_Registers + 0x34))

					/*****************USART*****************/
#define USART ((USART_t *)(IO_Registers + 0x09))					

					/*****************SPI*****************/
#define SPI ((SPI_t*)(IO_Registers + 0x0D))

					/*****************Timer*****************/
#define Timer0	((TIM0*)(0x52))
#define Timer1	((TIM1*)(IO_Registers + 0x26))
#define Timer2	((TIM2*)(IO_Registers + 0x22))
#define TIMCOM	((TIM012*)(0x58))



					/*****************ADC*****************/
#define ADC		((ADC_t * )(IO_Registers + 0x04))


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//General interrupt enable:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*

#define General_Interrupt_EN	(SREG |= (1 << 7))


//		|---------------------------------------|
//		|==================IVT==================|
//		|---------------------------------------|

#define RESET 1			//0x000	 External Pin, Power-on Reset, Brown-out Reset, Watchdog Reset, and JTAG AVR Reset
#define INT0 2			//0x002  External Interrupt Request 0
#define INT1 3			//0x004  External Interrupt Request 1
#define INT2 4			//0x006  External Interrupt Request 2
#define TIMER2_COMP 5	//0x008  Timer/Counter2 Compare Match
#define TIMER2_OVF 6	//0x00A  Timer/Counter2 Overflow
#define TIMER1_CAPT 7	//0x00C  Timer/Counter1 Capture Event
#define TIMER1_COMPA 8	//0x00E  Timer/Counter1 Compare Match A
#define TIMER1_COMPB 9	//0x010  Timer/Counter1 Compare Match B
#define TIMER1_OVF 10	//0x012  Timer/Counter1 Overflow
#define TIMER0_COMP 11	//0x014  Timer/Counter0 Compare Match
#define TIMER0_OVF 12	//0x016  Timer/Counter0 Overflow
#define SPI_STC 13		//0x018  SPI Serial Transfer Complete
#define USART_RXC 14	//0x01A  USART, Rx Complete
#define USART_UDRE 15	//0x01C  USART Data Register Empty
#define USART_TXC 16	//0x01E  USART, Tx Complete
#define _ADC 17			//0x020  ADC Conversion Complete
#define EE_RDY 18		//0x022  EEPROM Ready
#define ANA_COMP 19		//0x024  Analog Comparator
#define TWI 20			//0x026  Two-wire Serial Interface
#define SPM_RDY 21		//0x028  Store Program Memory Ready

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*
//Clock Macro:
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*


//#define F_CPU  8000000UL






#endif /* ATMEGA32_H_ */






/*





// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
// \\
  |
  |
  |
  |
  |
  |
  |
  |  
  |
  |
  |
  |
  |
_____  
















*/  