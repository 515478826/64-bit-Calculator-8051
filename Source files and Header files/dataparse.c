/*! 

 * @file    dataparse.c
 * @brief   dataparse file which responsible for parsing and checking data from user
 * @author  Ahmed Nasr Eldin 
 * @date    19/6/2015
 * @version 1.0
*/

/******************************************************************************************************************************
	                                 included files
******************************************************************************************************************************/

#include "dataparse.h"


unsigned char DATA_parse(big64_t * X_ptr , big64_t * Y_ptr ,uint8 * flag )
{
unsigned char Operation = 0 ;     /*User entered Operation */ 
uint8 UserInputData [38] ;        /*String to get data from user */
	uint8 * num11 ;									/*pointer to character represent the Low part from first operand */
	uint8 * num12 ;									/*pointer to character represent the High part from first operand */
  uint8 * num21 ;									/*pointer to character represent the Low part from Second operand */
	uint8 * num22 ; 								/*pointer to character represent the High part from second operand */
uint8 i=0,j = 0 ;                 /*used for itirations */
	uint8 length1 = 0 ;             /*length of first operand */
	uint8 length2= 0 ;							/*length of second operand */
	uint8 x;
	uint8 index ;                   /*Index of operation location */
	*flag=0;
UART_RecieveString(UserInputData) ;    /*Recieve data from user */

	
	
           /********* Check for first 0x from user input data *******************************/
if (!(UserInputData[0]=='0' && ((UserInputData[1]=='x')||UserInputData[1]=='X')))
{
*flag=2 ;  /*ERROR in Hexa input DATA */  

}
      /*****************Searching For OPeration in the String *******************************/

 while(!((UserInputData[i]=='\0')||(flag==1)))
  {
	if(!(UserInputData[i]=='*'||UserInputData[i]=='+')) 
	{
	*flag=3;       /*Not Supported Operaion **/

	}
	else 
	{
	Operation=UserInputData[i];
	*flag=1 ;                                  /*operation Found */
	length1=i-2 ;														   /*Set the length for first operand */
	length2=(strlen(UserInputData)-2)-(i+3) ;  /*Set the lengh for second operand */
	index= i ;

	break; 
}
i++ ;

}
  /********************     Check The Another Hexa Number   *******************/

 /****************** Check for 0x in the second number  ***********************/
if (!(UserInputData[index+1]=='0' && ((UserInputData[index+2]=='x')||UserInputData[index+2]=='X')))
{
*flag=2 ;                      /*ERROR in Hexa input DATA */  

}

/***********************   Check for all data in HEXA FORMAT *****************/
if((*flag)==1 )         /*check if there is no error */
{
	
	/*Check for data entered in Hexa */
for(j=2;j<(index)&&(*flag!=4);j++)
	{
/************** Check that all elements in hex format from 0--> F or 0---> f  *************/
		x=UserInputData[j];
if(!(((57>=x)&&(x>=48))||((70>=x)&&(x>=65))||((102>=x)&&(x>=97))))
	{
	*flag=4 ;
	}
	
	}
for(j=index+3;j<=(strlen(UserInputData)-2)&&(*flag!=4);j++)
	{
/************** Check that all elements in hex format from 0--> F or 0---> f  *************/

		x=UserInputData[j];
		
		if(!(((57>=x)&&(x>=48))||((70>=x)&&(x>=65))||((102>=x)&&(x>=97))))
	{
	
   	*flag=4 ;   /*Generate Error Data */
	}

}
}


/***************************** After Checking Parsing the Data *********************************/
if(*flag==1)
{
 num11=UserInputData+2 ;                  /*num11 = the address of the first number in the first operand */

	if(length1<=8)													/*if length<8 all data parsed in low 32 bit */
	{	
	*(num11+(length1+1))=NULL ;         		  /*Put Null after first operand */
	X_ptr->v[1]  = strtoul (num11, NULL, 16);   /*Big Endian  Low 32 bit in the higher address  */
	}
	else																					
	{
	*(num11+(length1+1))=NULL ;                 /*Put Null after first operand */
	num12 = ((num11+(length1))-8) ;	            /*num12 = the address of the Low 32 bit in the first operand */
	X_ptr->v[1]  = strtoul (num12, NULL, 16);   /*Big Endian  Low 32 bit in the higher address  */
	*num12=NULL ;                               /*  (*num12) = NULL after Conversion to convert the High 32 bit */
	X_ptr->v[0] = strtoul (num11, NULL, 16);		/*Big Endian  high 32 bit in the lower address  */
	}

num21=UserInputData+(index+3) ; 							 /*num21 = the address of the first number in the second operand */
*(num21+(length2+1))=NULL ;										/*Put Null after second operand */	
	if(length2<=8)																/*if length<8 all data parsed in low 32 bit */
	{
	
	Y_ptr->v[1]  = strtoul (num21, NULL, 16);   /*Big Endian  Low 32 bit in the higher address  */
	}
	else
	{
	num22=((num21+(length2))-8);								/*num12 = the address of the Low 32 bit in the second operand */
	Y_ptr->v[1]  = strtoul (num22, NULL, 16);   /*Big Endian  Low 32 bit in the higher address  */
	*(num22+1)=NULL ;                           /*  (*num22) = NULL after Conversion to convert the High 32 bit */
	Y_ptr->v[0] = strtoul (num21, NULL, 16);    /*Big Endian  high 32 bit in the lower address  */
	}

	
}

return Operation ;
}
