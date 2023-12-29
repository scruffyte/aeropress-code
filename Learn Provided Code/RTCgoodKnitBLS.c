
/* / *******************************************************************
// Developed from Code for the RTC DS1338 by BLS
// This code sets up the real time clock of the MCP79411 on the PIC18F45K20
// WriteI2C( 0b10000000 );   needs to happen once      // Make ST bit 1 (and zero seconds??)
// then remove from program with // as shown below
//
// As it stands this code will read the 
// The RTCC Register: 00h STbit  [10 Seconds] [Seconds]  Range: 00-59 
// and place the contents in inbitsecs 
// djs 16/12/16 

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
#include "p18f45k20.h"	//Pic18f45k20 header file

#include "i2c.h" 		//I2C header file
#include "delays.h"		//Delays header file


/** D E C L A R A T I O N S *******************************************/
/*#pragma code    // declare executable instructions

/** Function prototype declarations***************/


/** GLOBAL VARIABLE*******************************/
  unsigned char inbitsecs;


void main () 
{

 OpenI2C( MASTER, SLEW_OFF); //Initalise I2C module


SSPADD = 38; //sets I2C clock frequency this works with INT RC 4Mhz



while(1)
	//Read Time 
{
  StartI2C();                  // Start condition I2C on bus
  IdleI2C();
  putcI2C( 0xDE);            // addresses the RTCC chip with a write bit
  IdleI2C();
  putcI2C( 0x00 );         	// write register address (10 sec seconds on RTCC)
  IdleI2C();
 // WriteI2C( 0b10000000 );        // Make ST bit 1 (and zero seconds??) run code once with this line included
  RestartI2C(); 
  WriteI2C( 0xDF);            // addresses the chip with a read bit   
  IdleI2C();
  IdleI2C();
  inbitsecs =ReadI2C();				// read the 10 Sec Seconds
  StopI2C();                   // Stop condition I2C on bus
  StartI2C();                  // Start condition I2C on bus
  IdleI2C();
  putcI2C( 0xDE);            // addresses the chip
  IdleI2C();
  putcI2C( 0x00 );         	// write register address
  IdleI2C();
  RestartI2C(); 
  WriteI2C( 0xDF);            // addresses the RTCC chip with a read bit   
  IdleI2C();

  IdleI2C();
  inbitsecs=ReadI2C();	
  StopI2C();                   // Stop condition I2C on bu
  RestartI2C(); 
  WriteI2C( 0xDF);            // addresses the RTCC chip with a read bit   
  IdleI2C();

  IdleI2C();
  inbitsecs=ReadI2C();	
  StopI2C();               

}
}