/*! 

 * @file    uart.h
 * @brief   Uart header file driver 
 * @author  Ahmed Nasr Eldin 
 * @date    20/6/2015
 * @version 1.0
*/


#ifndef UART_H
#define UART_H
/******************************************************************************************************************************
	                                 included files
******************************************************************************************************************************/
#include<REG52.h>
/******************************************************************************************************************************
																		Defined Macros
******************************************************************************************************************************/
#define ENTER 13
#define CLS 0x0c
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for initializing the uart hardware for 8051 controller 
*@param this function takes void
[Returns] : void
--------------------------------------------------------------------------------------------------------------- **/
void UART_Init(void) ;
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for sending character through uart
*@param this function takes unsigned char represnt the character to be sent 
[Returns] : void
--------------------------------------------------------------------------------------------------------------- **/
void UART_Tx(unsigned char) ;
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for Recieving character from uart
*@param void
[Returns] : this function returns unsigned char represnt the character recieved from uart 
--------------------------------------------------------------------------------------------------------------- **/
unsigned char UART_Rx(void);
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for Sending String(array of characters) through uart
*@param ponter to character represent the string to be sent
[Returns] : void
--------------------------------------------------------------------------------------------------------------- **/
void UART_SendString(unsigned char * str) ;
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for Recieving String(array of characters) from uart
*@param ponter to character represent the string to be Recived 
[Returns] : void
--------------------------------------------------------------------------------------------------------------- **/

void UART_RecieveString(unsigned char * str ) ;










#endif