/*! 

 * @file    uart.h
 * @brief   Uart header file driver 
 * @author  Ahmed Nasr Eldin 
 * @date    20/6/2015
 * @version 1.0
*/
/******************************************************************************************************************************
	                                 included files
******************************************************************************************************************************/

#include "uart.h"

void UART_Init(void) {    
SCON  = 0x50;                         /**initalize uart to the following uart mode 1, 8-bit enable recieve*/   
TMOD |= 0x20;              				 /** using timer for generate 9600 baud by the following*/ 
	                                       /** TMOD: timer 1, mode 2, 8-bit auto reload*/  
TH1   = 0xFD;           		    /** TH1:  reload value for 9600 baud @ 11.0592MHz*/   
TR1   = 1;                 										 /* start  timer 1*/   
}

/*uart transmission function */
void UART_Tx(unsigned char x) {           /**function paramaters(x)is character to be sent to uart*/
SBUF=x; 															 	//place value to be sent in buffer
while (TI==0);									   			 // wait till flag becom 1
TI=0;    														 	 //clear the flag
}
unsigned char UART_Rx(void)
{
while(RI==0);
	RI=0;                           /*Clear The Flag */
return (unsigned char)SBUF ;
	
}
void UART_SendString(unsigned char * str){       /**function paramaters is(*str) pointer to character to be sent to uart*/
   while(*str!='\0'){   										//sending data till finding null terminato 
    UART_Tx(*str++) ;           											// value to be sent
	  
              																					//go to next character 
   }
 }
void UART_RecieveString(unsigned char * str )
{
do {

	*str=UART_Rx() ;
	UART_Tx(*str);
		}while(*str++!=13) ;
*str='\0';                        /*Put Null Terminator at End of String */
}