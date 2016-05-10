/*! 

 * @file    calc.h
 * @brief   calculation file which responsible for performing arithmetic operation for 64 bit data
 * @author  Ahmed Nasr Eldin 
 * @date    20/6/2015
 * @version 1.0
*/


#ifndef CALC_H
#define CALC_H
/******************************************************************************************************************************
	                                 included files
******************************************************************************************************************************/
#include "std_types.h"
/******************************************************************************************************************************
																		Defined Macros
******************************************************************************************************************************/
#define MAX(A,B) ((A)>(B)?(A):(B))    /*get max beween two numbers */
#define MAX_VAL_32 0xffffffff         /*MAX value of unsigned 32 bit number */ 
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for adding two 64 bit unsigned integer and return data into 128 bit data
*@param this function takes 2 Arguments 
				1-Pointer to big64_t Struct which represent first operand 
				2-Pointer to big64_t Struct which represent second operand 
[Returns] : This function returns big128_t which represent the result of summation
--------------------------------------------------------------------------------------------------------------- **/
big128_t addFun(big64_t * ,big64_t *);
/** ---------------------------------------------------------------------------------------------------------------
@brief This function is responsible for Multiply two 64 bit unsigned integer and return data into 128 bit data
*@param this function takes 2 Arguments 
				1-Pointer to big64_t Struct which represent first operand 
				2-Pointer to big64_t Struct which represent second operand 
[Returns] : This function returns big128_t which represent the result of Multiplication
--------------------------------------------------------------------------------------------------------------- **/
big128_t MULT1(big64_t x, big64_t y) ;


#endif
