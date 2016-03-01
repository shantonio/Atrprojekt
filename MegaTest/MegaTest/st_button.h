/*
* st_button.h
*
* Created: unknown
* Author: unknown
*/

#ifndef  st_button_h
#define  st_button_h

#include <stdint-gcc.h>

class Button{
public:
	Button( volatile uint8_t *reg, uint8_t pin, bool pullUp );	
	void Check();	
	bool IsPressed();
private:
	volatile uint8_t *reg;
	uint8_t pin;
	bool press;
	bool p_edge;
};
#endif //st_button_h