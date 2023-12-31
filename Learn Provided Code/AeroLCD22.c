/* DJS 12/02/18 ***********************************************************/
// Adapting LCD.c by DW Smith, 25 January 2012 for 18F45K20 LCD BSc PD&T
// E on D7, RS on D6,  D4-7 on PIC: D0-3.
// V7 DJS/RK 10/2019
// Revisited DJS 06/10/22 message char string process
//*************************************************************************/
// #pragma config FOSC = INTIO67
// #pragma config WDTEN = OFF, LVP = OFF, MCLRE = OFF
/*                                                                          */

#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF, MCLRE = ON


#include "p18f45k20.h"

#include <delays.h>

#define CLEAR_SCREEN  	0b00000001
#define FOUR_BIT  		0b00101100
#define LINES_5X7  		0b00111000
#define CURSOR_BLINK  	0b00001111
#define CURSOR_RIGHT  	0b00000110

#define DATA_PORT  LATD
#define RS_PIN     PORTDbits.RD6
#define E_PIN      PORTDbits.RD7


void Delay5milli(void)							//Suitable delay for LCD
{
Delay1KTCYx(2);           						
}


void SetAddr(unsigned char DDaddr)
{
        DATA_PORT &= 0xf0;                      // Write upper nibble
        DATA_PORT |= (((DDaddr | 0b10000000)>>4) & 0x0f);
                        
        RS_PIN = 0;                             // Set control bit
      	Delay5milli();
        E_PIN = 1;                              // Clock the cmd and address in
        Delay5milli();
        E_PIN = 0;

		DATA_PORT &= 0xf0;                      // Write lower nibble
        DATA_PORT |= (DDaddr&0x0f);

		Delay5milli();
        E_PIN = 1;                              // Clock the cmd and address in
        Delay5milli();
        E_PIN = 0;
}

void WriteCmd(unsigned char cmd)
	{
        DATA_PORT &= 0xf0;
        DATA_PORT |= (cmd>>4)&0x0f;           
        RS_PIN = 0;                     		// Set control signals for command
        Delay5milli();
        E_PIN = 1;                      		// Clock command in
        Delay5milli();
        E_PIN = 0;

       	
        DATA_PORT &= 0xf0;              		// Lower nibble interface
        DATA_PORT |= cmd&0x0f;
		Delay5milli();
        E_PIN = 1;                      		// Clock command in
        Delay5milli();
        E_PIN = 0;
	}

void WriteChar(char data)
{
        DATA_PORT &= 0xf0;
        DATA_PORT |= ((data>>4)&0x0f);

		RS_PIN = 1;                     		// Set control bits
        Delay5milli();
        E_PIN = 1;                      		// Clock nibble into LCD
        Delay5milli();
        E_PIN = 0;

		    
        DATA_PORT &= 0xf0;              		// Lower nibble interface
        DATA_PORT |= (data&0x0f);
        
        Delay5milli();
        E_PIN = 1;                      		// Clock nibble into LCD
        Delay5milli();
        E_PIN = 0;
}

 void WriteString(const rom char *buffer)    
{		 
        while(*buffer)                  		// Write data to LCD up to null
        {
          Delay5milli();
          WriteChar( *buffer);          		// Write character to LCD
          buffer++;                     		// Increment buffer
        }
        return;
}       

void main (void)
{

//SET UP

   

   	ANSEL  = 0;	                        	    //turn off all analog inputs
	ANSELH = 0; 
   	TRISD  = 0b00000000;                 		//sets PORTd
   	LATD   = 0b00000000;	                	//turns off PORTd outputs, good start position   	

	// this code configures the display  
 	
	WriteCmd ( 0x02 );							// sets 4bit operation
	WriteCmd ( CLEAR_SCREEN);		
	WriteCmd ( FOUR_BIT & LINES_5X7 );			// sets 5x7 and multiline operation.
	WriteCmd ( CURSOR_BLINK );					// blinks cursor
	WriteCmd ( CURSOR_RIGHT  );					// moves cursor right	
	
	
// Start of user program

	WriteChar('I');				
	SetAddr  (0x88);		
	Delay1KTCYx(5);                            //delay	                 				
	WriteString("dislike");	
	//WriteChar('*');	                            //space

	   
    SetAddr (0xC0);                             // moves character to begining of second line
    WriteString("Aeropress");
	WriteChar('C');
    WriteString("offee"); 
	
	SetAddr  (0xCF);
    WriteChar(0xE0);                           // writes one of the stored ASCII characters
while (1);				                 		//stop the program - Loop here forever
	
}