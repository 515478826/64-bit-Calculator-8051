/*! 

 * @file    dataparse.h
 * @brief   dataparse file which responsible for parsing and checking data from user
 * @author  Ahmed Nasr Eldin 
 * @date    19/6/2015
 * @version 1.0
*/


#ifndef DATA_PARSE
#define DATA_PARSE
/******************************************************************************************************************************
	                                 included files
******************************************************************************************************************************/
#include "std_types.h"
#include "uart.h"
#include <string.h>
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for Checking and Parsing data from user into 64 bit integer
*@param this function takes 3 Arguments 
				1-Pointer to big64_t Struct which used to return first operand from user
				2-Pointer to big64_t Struct which used to return second operand from user
				3-pointer to uint8 which used to indicate whether user enterd data in correct format or not
[Returns] : This function returns unsigned char represent the entered operation 
--------------------------------------------------------------------------------------------------------------- **/
unsigned char DATA_parse(big64_t * X_ptr , big64_t * Y_ptr ,uint8 * flag ) ;

#endif