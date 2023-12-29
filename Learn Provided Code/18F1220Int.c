//RBchange Interrupt    edited DW Smith    9th February 2012 by DJS Nov2021
#include <p18f1220.h>
#pragma config WDT=OFF , OSC=INTIO2 , PWRT = ON, LVP=OFF, MCLRE = OFF
#include <delays.h>
#pragma interrupt isr	// declares isr as my interrupt (service) routine.

int PORTBtemp;  //the state of PORTB is stored here on interrupt.

#pragma code isr = 0x08
void isr(void)
{
PORTBtemp = PORTB;
PORTB = 0xFF;
Delay100TCYx(78);
PORTB = 0;
Delay100TCYx(78);
PORTB = 0xFF;
Delay100TCYx(78);
PORTB = 0;
Delay100TCYx(78);
PORTB = PORTBtemp;
INTCONbits.RBIF = 0; 	// clear RBIF
}
#pragma code

void main (void)
{
	//SET UP
   	// OSCCON defaults to 31kHz. So no need to alter it.
    ADCON1 = 0x7F;  //all IO are digital  or 0b01111111 in binary
   	TRISA = 0b11111111;	//sets PORTA as all inputs
   	PORTA = 0b00000000;	//turns off PORTA outputs, not required, no outputs    	
   	TRISB = 0b10000000;	//sets PORTB,7 is I/P 
    PORTB = 0b00000000;	//turns off PORTB outputs, good start position
	INTCON2bits.RBPU=0;	
	INTCON = 0b10001000;  //sets GIE,RBIE
	
	
	while (1)
	{	
	PORTB = 0b00000001;		// "Knightrider" LEDs when program running normally
	Delay100TCYx(156);
	PORTB = 0b00000010;		//
	Delay100TCYx(156);
	PORTB = 0b00000100;		// 
	Delay100TCYx(156);
	PORTB = 0b00001000;		//
	Delay100TCYx(156);
	PORTB = 0b00010000;		//
	Delay100TCYx(156);
	PORTB = 0b00100000;		// 
	Delay100TCYx(156);
	PORTB = 0b01000000;		//
	Delay100TCYx(156);	
	}
}