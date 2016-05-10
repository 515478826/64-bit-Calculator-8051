#define doxygen
#ifdef doxygen
/*! \file std_type.h
    \brief standard types header file used for the program
		Details.

* @file    std_type.h
* @brief   Standard Types header file for this program 
* @author  Ahmed Nasr Eldin 
* @date    8/1/2014
* @version 1.0
 */
#endif
#ifndef STD_TYPE_H_
#define STD_TYPE_H_
#include <stdio.h>
//#include  <inttypes.h>

#include <stdlib.h>
typedef unsigned char uint8;    /**use uint8 as one byte data type**/
typedef unsigned short uint16;  /**use uint16 as two bytes data type**/
typedef unsigned long uint32;   /**use uint16 as four bytes data type**/
typedef char sint8 ; 
struct big64
{
	uint32 v[2]; /* num = v[0] + (v[1] << 32)  - "little endian" */
};
typedef struct big64 big64_t;
 
struct big128
{
	uint32 v[4];
};
typedef struct big128 big128_t;
//typedef unsigned long long uint64
#endif /* std_type_h_ */