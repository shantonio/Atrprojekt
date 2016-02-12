/* 
* Servo.cpp
*
* Created: 09.02.2016 13:35:08
* Author: shantonio
*/


#include "Servo.h"

// default constructor
Servo::Servo():_miPostition(0)
{} //Servo

//  constructor 1
Servo::Servo(int pos)
{
this->_miPostition=pos; // einfach nur so wird nirgendwo benutzt
} //Servo

// default destructor
Servo::~Servo() {} //~Servo

/**************************************************************************************************
Timer/Counter 1, 3, 4, and 5) ONLY FOR 1,3,4,5
 16 Bit Timer	// set PWM for  duty cycle @ 16bit Pulse width vary between 0.5 0% and 2.5ms 100%
PWM_frequency = clock_speed / (2 * Prescaller_value * TOP_value )
ICR1 = 0xFFFF;									//ICR1 =65535 as TOP_value
ICR1 =20000 T=20ms  as TOP für 50 HZ PWM  extra für servo
****************************************************************************************************/
void Servo::initTimer1PWM()	
{
	//	DDRB |= (1<<PORTB7)| (1<<PORTB6)|(1<<PORTB5);				//Set OC1A, OC1B and OC1C as Output in Data Direction Register for PWM
	  DDRB |= (1<<PB7)| (1<<PB6)|(1<<PB5);						//Set OC1A, OC1B and OC1C as Output in Data Direction Register for PWM
	//	DDRB=0xE0;													//Set OC1A, OC1B and OC1C as Output in Data Direction Register for PWM
		
		
		//TCCR1B |= (1 << CS00);							//  the timer with NO prescaler
		//TCCR1B |= (1 << CS11);							// the timer with prescalar at 8
		sbi(TCCR1B,CS11);									// ganau das gleiche wie OBEN prescalar at 8
		ICR1 = 20000;										//ICR1 =20000 T=20ms  as TOP für 50 HZ PWM  extra für servo
		

		TCCR1A |= (1 << COM1A1)|(1 << COM1B1)|(1 << COM1C1);
		// set none-inverting mode

		TCCR1A |= (1 << WGM11);
		TCCR1B |= (1 << WGM13);
		//PWM, Phase Correct  With ICR1 as TOP
		
		// Phi =0 wenn OCR1A= 500;Phi =180 wenn OCR1A= 2500 jede Grad + 11.11
		OCR1A = 500+90*11.11;									//  set PWM for 0% duty cycle @ 16bit Pulse width vary between 0.5 and 2.5ms (von 0-180)
		OCR1B = 500+180*11.11;
		OCR1C = 500+0*11.11;
}
