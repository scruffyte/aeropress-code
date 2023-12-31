/* DJS 12/02/18 ***********************************************************/
// Originally adapted from LCD.c by DW Smith, 25 January 2012 for 18F45K20 LCD BSc PD&T
// E on D7, RS on D6,  D4-7 on PIC: D0-3.
// V7 DJS 10/2019 V8 DJS 18/02/21 Changed Message Tidied Up
// MCLRE = OFF SO PROG WILL RUN IN RELEASE
// 04/03/21 DJS added CG Capability write Custom Graphics Caracters to LCD initially
// THEN to the screen 04/03/21 REVISED DJS V4 15/10/21 checked 13/10/23 DJS
//*************************************************************************/



#pragma config FOSC = INTIO67
#pragma config WDTEN = OFF, LVP = OFF, MCLRE = OFF


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


 // this code configures the display  
  
	WriteCmd ( 0x02 );							// sets 4bit operation
	WriteCmd ( CLEAR_SCREEN);		
	WriteCmd ( FOUR_BIT & LINES_5X7 );			// sets 5x7 and multiline operation.
	WriteCmd ( CURSOR_BLINK );					// blinks cursor
	WriteCmd ( CLEAR_SCREEN );

	SetAddr	 ( 0x00 );
	WriteChar ( 0x00 );
	WriteChar ( 0x01 );
	WriteChar ( 0x02 );
	WriteChar ( 0x03 );
	WriteChar ( 0x04 );
	WriteChar ( 0x05 );
	WriteChar ( 0x06 );
	WriteChar ( 0x07 );

	WriteCmd  ( 0x40 );							// WRITING TO LCD MEMORY
	WriteCmd  ( 0b00001011);	//display off
	WriteChar ( 0b00000000 );					// first character
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00011111 );

	WriteChar ( 0b00000000 );					// second character
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00011111 );
	WriteChar ( 0b00000000 );

	WriteChar ( 0b00000000 );					// third character
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00011111 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );

	WriteChar ( 0b00000000 );					// fourth character
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00011111 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );

	WriteChar ( 0b00000000 );					// fifth character
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00011111 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );

	WriteChar ( 0b00000000 );					// sixth character
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00011111 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );

	WriteChar ( 0b00000000 );					// seventh character
	WriteChar ( 0b00011111 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );

	WriteChar ( 0b00011111 );					// eigth character
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );
	WriteChar ( 0b00000000 );

	WriteCmd  ( 0b00001100);	//display back on
	WriteCmd  ( CLEAR_SCREEN);     
	
// Start of user program
    SetAddr (0x80); 
	WriteChar ( 0x00 );   // NOW WRITING THE CHARACTERS TO ACTUALLY APPEAR ON THE DISPLAYT
	WriteChar ( 0x01 );
	WriteChar ( 0x02 );
	WriteChar ( 0x03 );
	WriteChar ( 0x04 );
	WriteChar ( 0x05 );
	WriteChar ( 0x06 );
	WriteChar ( 0x07 );



	   
    SetAddr (0xC0);                             // moves character to begining of second line
    WriteString("Steps");
while (1);				                 		//stop the program - Loop here forever
	
}
