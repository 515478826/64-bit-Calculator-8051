/****************************************************************************
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Console mode (command line) program.                           *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
/****************************************************************************
 *                                                                          *
 * Function: main                                                           *
 *                                                                          *
 * Purpose : Main entry point.                                              *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

struct big64
{
	uint32_t v[2]; /* num = v[0] + (v[1] << 32)  - "little endian" */
};
typedef struct big64 big64_t;
 
struct big128
{
	uint32_t v[4];
};
typedef struct big128 big128_t;


big128_t MULT1(big64_t x , big64_t y);

int main(int argc, char *argv[])
{
    /* TODO: Enter code here */
	uint64_t x=0 , y=0 ; 
	big64_t var1,var2 ;
	big128_t op ;
	char i=0 ;
printf("64 bit calculator\n") ;
printf("Type the expression then press enter:\n") ;
printf("Enter the first number:") ;
scanf("%x",&x);
printf("Enter the second number:") ;
scanf("%x",&y);
var1.v[0]=(uint32_t)x ;
var1.v[1]=(uint32_t)(x>>32) ;
var2.v[0]=(uint32_t)y ;
var2.v[1]=(uint32_t)(y>>32) ;
op = MULT1(var1,var2) ;
	for(i=3;i>=0;i--)
	printf("%x",op.v[i]) ;
printf("\n");
 _getch();
   return 0;
	
}
big128_t MULT1(big64_t x , big64_t y)
{
	uint8_t i ,j ;
	big128_t p1 ;
	uint32_t arr[16];
	uint32_t arr2[6] ;
uint16_t * op,ptr2 ;
uint16_t * ptr  ;
uint16_t * ptr1 ;
ptr = (uint16_t *)&(x.v) ;
ptr1 =(uint16_t *)& (y.v) ;
op = (uint16_t *)&(p1.v) ;
for(j=0;j<4;j++){
for(i=0;i<4;i++)
	{
arr[i+(j*4)]=ptr[j] * ptr1[i] ;
}
 }

		
	op[0]=(uint16_t) arr[0] ;
	/****************************************/
	arr2[0]=(arr[1]+arr[4]+(arr[0]>>16));
	op[1]=(uint16_t)arr2[0] ;
	/****************************************/
	arr2[1]=(arr[2]+arr[5]+arr[8]+(arr2[0]>>16)) ;
	op[2]=(uint16_t)arr2[1] ;
	/*****************************************/
	arr2[2]=(arr[3]+arr[6]+arr[9]+arr[12]+(arr2[1]>>16)) ;
	op[3]=(uint16_t)arr2[2] ;
	/********************************/
	arr2[3]=(arr[7]+arr[10]+arr[13]+(arr2[2]>>16)) ;
	op[4]=(uint16_t)arr2[3] ;
arr2[4]=(arr[11]+arr[14]+(arr2[3]>>16)) ;
	op[5]=(uint16_t)arr2[4] ;
arr2[5]=(arr[15]+(arr2[4]>>16)) ;
	op[6]=(uint16_t)arr2[5] ;
	op[7]=(uint16_t)(arr2[5]>>16) ;  /*last carry */
return p1;
}

