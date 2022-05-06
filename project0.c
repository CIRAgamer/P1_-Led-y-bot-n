/*
 * GPIO.c
 *
 *  Created on: 19 sep. 2021
 *      Author: Richard
 *       GPIO Port A (APB): 0x4000.4000
        GPIO Port B (APB): 0x4000.5000
        GPIO Port C (APB): 0x4000.6000
        GPIO Port D (APB): 0x4000.7000
        GPIO Port E (APB): 0x4002.4000
        GPIO Port F (APB): 0x4002.5000

RCGCGPIO |= 0x01 //Enable clock for PORTA
RCGCGPIO |= 0x02 //Enable clock for PORTB
RCGCGPIO |= 0x04 //Enable clock for PORTC
RCGCGPIO |= 0x08 //Enable clock for PORTD
RCGCGPIO |= 0x01 //Enable clock for PORTE
RCGCGPIO |= 0x02 //Enable clock for PORTF

 */
#include "include.h"

#define SYSCTL_RCGCGPIO_R (*(( volatile unsigned long *)0x400FE608 ) ) //fisico del RCGCGPIO  no cambia
#define GPIO_PORTD_DATA_R (*(( volatile unsigned long *)0x40007038 ) ) //** 0x40007000+x38
#define GPIO_PORTD_DIR_R  (*(( volatile unsigned long *)0x40007400 ) ) //     7000+x400                                                    
#define GPIO_PORTD_DEN_R  (*(( volatile unsigned long *)0x4000751C ) ) // fisico GPIODATA 0x40007000+0x51c


int main ( void )
{
SYSCTL_RCGCGPIO_R |= 0x08; // reloj D
GPIO_PORTD_DEN_R  = 0x0E;  // pin 1-3 como digital
GPIO_PORTD_DIR_R  = 0x0E;  // salida de pin 1-3
		
	while (1) 
		{  
		GPIO_PORTD_DATA_R |= 0x04; // led azul
		}
}