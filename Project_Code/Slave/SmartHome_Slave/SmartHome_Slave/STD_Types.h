/**************************************/
/* Description : Standard Types lib   */
/* Author      : Abo elnour           */
/* Version     : 0.2v                 */
/* Date        : 25 Nov 2022          */
/* History     : 0.1v initial creation*/
/*               0.2v add error status*/
/*               enum                 */
/**************************************/

#ifndef  STD_TYPES_H
#define  STD_TYPES_H

typedef   unsigned char      uint8  ;
typedef   unsigned short int uint16 ;
typedef   unsigned long  int uint32 ;
typedef   signed char        sint8  ;
typedef   signed short int   sint16 ;
typedef   signed long  int   sint32 ;
typedef   float              float32 ;
typedef   double             float64 ;
typedef   long double        float128 ;

typedef enum 
{
	EOK  ,
	ENOK  ,
	PARAM_OUT_RANGE,
	PARAM_NULL_PTR 
}tenuErrorStatus;

#define NULL_PTR (void *) 0

#endif



