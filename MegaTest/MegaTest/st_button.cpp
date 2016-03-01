/*
* st_button.cpp
*
* Created: unknown
* Author: unknown
* modified by: C. Gries, 14.08.2015
*/

#ifndef  st_button_cpp
#define  st_button_cpp

// Change by C. Gries Start

// Change by C. Gries End

#include "Macros.h"//< bit operation macros
#include <avr/io.h>            //< I/O access
//#include "avr/iomxx0_1.h"
#include "st_button.h"         //< Header

Button::Button( volatile uint8_t *reg, uint8_t pin, bool pullUp  ){
	this->reg = reg;
	this->pin = pin;

	p_edge    = true;
	// Change by C. Gries Start
	// pull up resistor
	if(pullUp)
	{
		// Address Pin register +2 = Address Port Register, see iom8.h, 
		// http://www.mikrocontroller.net/topic/136918
			SET( *reg, pin );  
	}
	// Change by C. Gries End
}
	
void Button::Check(){
	if( IS_SET(*reg,pin) ){     // button is not pressed.
		p_edge = true;
	}
	else if(p_edge){                     // button is just pressed.
		p_edge = false;
		press  = true;
	}
}
	
bool Button::IsPressed(){
	if(!press)
		return false;
	press  = false;
	return true;
}

#endif //st_button_cpp