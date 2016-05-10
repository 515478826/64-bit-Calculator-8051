/*! 

 * @file    app.c
 * @brief   Application file 
 * @author  Ahmed Nasr Eldin 
 * @date    20/6/2015
 * @version 1.0
*/
/******************************************************************************************************************************
	                                 included files
******************************************************************************************************************************/
#include "uart.h"
#include "calc.h"
#include "dataparse.h"

void main()
{
	/****************** Definitions of Variables**************/
	uint8 str [9] ;      /*String used to print output on screen */
	uint32 Data;         
	big64_t x ;				 	/*first Operand */ 
	uint8 flag ;				/*flag to check data parsing */
  sint8 i = 0;				/*used for itiraton */
	big64_t y ;					/*Second operand */
	big128_t z ;				/*Output variable used to store data after the operation */
	uint8 op ;					/*Char to contain the operation */
	
	/*************** Initialization of operands and uart ******************/
	
	x.v[0]=0; 					
	x.v[1]=0;
	y.v[0]=0;
	y.v[1]=0;	
	UART_Init() ;
	/****************** the Application ************************************/

for(;;) {
	UART_SendString("64 Unsigned Number Calculator") ;
	UART_Tx(ENTER) ;																									/*Enter to new line */
	UART_SendString("Type the expression then press enter:")	;
	UART_Tx(ENTER) ;
	op=DATA_parse(&x,&y,&flag) ;              /*Parse data and return the operation */

	switch((flag))                         /*check the data enterd was correct or not */
	{
		case 1 :                            /*Data check passed */
   if(op=='+')
	 {
 z=addFun(&x,&y) ;                     /*add the two 64 bit numbers */
	UART_SendString("Result");
	UART_Tx(ENTER) ;
UART_SendString("0x");
 /****************** Display the Result ********************/
		 for(i=0;i<4;i++)
		{
		Data=z.v[i] ;
		sprintf(str,"%lx",Data);       /*Convert the hex data to string */
		UART_SendString(str);
		}
	 }
		break;
	/****************** Commented code becasuse of code size and Evaluation version ****************/
	 /*		case 3 :
			UART_SendString("Not Supported operation");
			break ;
			case 2:
		  case 4 :
	   UART_SendString("Plz Enter Data in hex format");*/
		default:                  		   /*if flag !=1   print errot on terminal */ 
	UART_SendString("ERROR");
		break;

	}
	while((UART_Rx()!=ENTER));                /*Wait till user press enter */ 
	UART_Tx(CLS); 											   	 	 /*Clear Terminal */
	}
}