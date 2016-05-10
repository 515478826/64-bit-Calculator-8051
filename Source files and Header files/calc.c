/*! 

 * @file    calc.c
 * @brief   calculation file which responsible for performing arithmetic operation for 64 bit data
 * @author  Ahmed Nasr Eldin 
 * @date    20/6/2015
 * @version 1.0
*/

#include "calc.h"
big128_t addFun(big64_t * ptr_x , big64_t * ptr_y )
{

	uint32 Low_Part ;
	uint32 High_Part ;
	uint8 Carry=0,Carry2=0 ;
	big128_t op  ;
	uint8 i ;
	/*initialize 128 data by zero  */
	for(i=0;i<4;i++)	
	{
	op.v[i]=0;
	}
 Low_Part=ptr_x->v[1] + ptr_y->v[1] ;

	if(Low_Part<(MAX(ptr_x->v[1],ptr_y->v[1])))  /*Check For Overflow */ 

	{
		Carry = 1 ;
		Low_Part = (MAX_VAL_32-1) ;
	}
	High_Part=(ptr_x->v[0] + ptr_y->v[0]+Carry ) ;

	if(High_Part<(MAX(ptr_x->v[0],ptr_y->v[0])))  /*Check For Overflow */ 
	{

	Carry2 = 1 ;
	High_Part = (MAX_VAL_32-1)+Carry ;
	}
	op.v[3]=Low_Part  ;          /*Assign data for op */
	op.v[2]=High_Part ;					/*Assign data for op */
	op.v[1]=Carry2;							/*Assign data for op */
return op ;
}





/*****NOT Compiled code because Evaluation version and Exceed the limited code size  ***********/ 

#ifdef  MULTIPLY 

big128_t MULT1(big64_t x , big64_t y)
{
	uint8 i ,j ;
	big128_t p1 ;
	uint32 arr[16];
	uint32 arr2[6] ;
  uint16 * op,ptr2 ;
	uint16 * ptr  ;
	uint16 * ptr1 ;
	ptr = (uint16 *)&(x.v) ;
	ptr1 =(uint16 *)& (y.v) ;
	op = (uint16 *)&(p1.v) ;

	for(j=0;j<4;j++)
	{
	for(i=0;i<4;i++)
	{
	arr[i+(j*4)]=ptr[j] * ptr1[i] ;
	}
	}	
		
	op[0]=(uint16) arr[0] ;
	/****************************************/
	arr2[0]=(arr[1]+arr[4]+(arr[0]>>16));
	op[1]=(uint16)arr2[0] ;
	/****************************************/
	arr2[1]=(arr[2]+arr[5]+arr[8]+(arr2[0]>>16)) ;
	op[2]=(uint16)arr2[1] ;
	/*****************************************/
	arr2[2]=(arr[3]+arr[6]+arr[9]+arr[12]+(arr2[1]>>16)) ;
	op[3]=(uint16)arr2[2] ;
	/********************************/
	arr2[3]=(arr[7]+arr[10]+arr[13]+(arr2[2]>>16)) ;
	op[4]=(uint16)arr2[3] ;
	arr2[4]=(arr[11]+arr[14]+(arr2[3]>>16)) ;
	op[5]=(uint16)arr2[4] ;
	arr2[5]=(arr[15]+(arr2[4]>>16)) ;
	op[6]=(uint16)arr2[5] ;
	op[7]=(uint16)(arr2[5]>>16) ;  /*last carry */
	return p1;
	}
#endif














/* Not Compiled function because of problems with inline assembly */

#ifdef ADDASSEMBLY
big128_t addFun(big64_t * ptr_x , big64_t * ptr_y )
{
	uint8 x=1 ; 
	uint8 y =1;
	uint8 z =2;
	uint8 v1[8];
	uint8 v2[8] ;
	big128_t Data;
	uint8 * ptr ;
	ptr=(uint8 * ) & Data ;
	UART_SendString("Calc Iam called") ;
v1[0]=(uint8)ptr_x->v[1]>>24;
v1[1]=(uint8)ptr_x->v[1]>>16 ;
v1[2]=(uint8) ptr_x->v[1]>>8;
v1[3]=(uint8)ptr_x->v[1];     /*least significnt byte */
	v1[4]=(uint8)ptr_x->v[0]>>24;
v1[5]=(uint8)ptr_x->v[0]>>16 ;
v1[6]=(uint8) ptr_x->v[0]>>8;
v1[7]=(uint8) ptr_x->v[0];     /*least significnt byte */
	/**************** Second Variable ********/
	v2[0]=(uint8)ptr_y->v[1]>>24;
v2[1]=(uint8)ptr_y->v[1]>>16 ;
v2[2]=(uint8) ptr_y->v[1]>>8;
v2[3]=(uint8) ptr_y->v[1];     /*least significnt byte */
	v2[4]=(uint8)ptr_y->v[0]>>24;
v2[5]=(uint8)ptr_y->v[0]>>16 ;
v2[6]=(uint8) ptr_y->v[0]>>8;
v2[7]=(uint8) ptr_y->v[0];     /*least significnt byte */
#pragma asm
ADD A,v[0] ;   
MOV A,x ;
ADD A,y ;
MOV z,A ;	
	#pragma	endasm

}
}
#else

#endif
