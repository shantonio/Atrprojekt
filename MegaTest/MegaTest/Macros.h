/*
 * Macros.h
 *
 * Author: Stevie Andrea Lucardi; 16.06.2013
 * modified by: Chris Gries, 08.08.2015
 */

#ifndef  __MACROS_H__
#define  __MACROS_H__

// Simple math functions, C. Gries
/// Type-independent MAX-function with two operands
#define MAX(x,y)    ( ( (x) > (y) ) ?  (x) : (y) ) 
/// Type-independent MIN-function with two operands
#define MIN(x,y)    ( ( (x) < (y) ) ?  (x) : (y) )  
/// Type-independent ABS-function with two operands
#define ABS(x)      ( ( (x) <  0  ) ? -(x) : (x) )  

// Bit operation functions, S. Lucardi, comments by C. Gries
/// Set bit y in register x
#define SET(x,y)    ( x |=   1<<y  )                     
/// Unset bit y in register x
#define RES(x,y)    ( x &= ~(1<<y) )                    
/// Check whether bit y in register x is set
#define IS_SET(x,y) ( x &    1<<y  )                   
/// Check whether bit y in register x is not set
#define IS_RES(x,y) ( ~IS_SET(x,y) ) 

#endif //__MACROS_H__