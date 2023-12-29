
/* / *******************************************************************
// Adapted from PIC18F45K20 PICkit 3 Debug Express Demo Board Lesson 7 - ADC
// by DJS/RK 27/09/16
// revised djs 05/0218
// further revised djs 11/10/18 to remove PORTB output
// can be used to check 18F45K20 PCB in HARDWARE DEBUG set up WATCH Window
// This code sets up the Analog-to-Digital-Converter on the PIC18F45K20
// to convert the voltage on pin RA0 to a digital value and output the 8 msbs
// of that converted code to PORTB then repeat........
//
// *******************************************************************
// *    See included documentation for Lesson instructions           *
// *******************************************************************

/** C O N F I G U R A T I O N   B I T S ******************************/

#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF                       // CONFIG1H
#pragma config PWRT = OFF, BOREN = OFF, BORV = 30                        // CONFIG2L
#pragma config WDTEN = OFF, WDTPS = 32768                                     // CONFIG2H
#pragma config MCLRE = ON, LPT1OSC = OFF, PBADEN = ON, CCP2MX = PORTC       // CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF                          // CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF                   // CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                         // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF               // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                           // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF           // CONFIG7L
#pragma config EBTRB = OFF                                                  // CONFIG7H

/** I N C L U D E S **************************************************/
#include "p18f45k20.h"
#include "07 ADC.h"  // header file
#include <delays.h>


/** D E C L A R A T I O N S *******************************************/
#pragma code    // declare executable instructions

void main (void)
{

    // Init I/O
//    TRISB = 0b00000000;     	// PORTB bits 7:0 are all outputs (0)
	TRISAbits.TRISA0 = 1;		// TRISA0 = 1 RA0 = input

    // ADCON1 is now set up in the InitADC() function.

    // Init ADC
 		while (1)
    {

    ADC_Init();
    ADC_Convert();
//	LATB = ADRESH;
	Delay10KTCYx(25);           //delay 25 x 10000 cycles Run To Cursor and Change RA0 voltage

	}
 
}

void ADC_Init(void)
{ 	
	// initialize the Analog-To-Digital converter.
    // First, we need to make sure the AN0 pin is enabled as an analog input
    // as the demo board potentiometer is connected to RA0/AN0
    // Don't forget that RB0/AN12 must be digital!

	ANSEL = 0;	//turn off all other analog inputs
	ANSELH = 0;
 	ANSELbits.ANS0 = 1;	// turn on RA0 analog

    // Sets bits VCFG1 and VCFG0 in ADCON1 so the ADC voltage reference is VSS to VDD

    ADCON1 = 0;
    
    //
    // ADFM = 0 so we can easily read the 8 Most Significant bits from the ADRESH
    // Special Function Register
    
	ADCON2 = 0b00111000;

    // Select channel 0 (AN0) to read the An0 voltage and turn on ADC
    ADCON0 = 0b00000001;

}

unsigned char ADC_Convert(void)

{ // start an ADC conversion and return the 8 most-significant bits of the result
    ADCON0bits.GO_DONE = 1;             // start conversion
    while (ADCON0bits.GO_DONE == 1);    // wait for it to complete
    return ADRESH;                      // return high byte of result
}
