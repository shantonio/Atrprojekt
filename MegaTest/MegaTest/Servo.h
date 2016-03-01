/* 
* Servo.h
*
* Created: 09.02.2016 13:35:08
* Author: shantonio
*/

#ifndef __SERVO_H__
#define __SERVO_H__

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <avr/io.h>



#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


class Servo
{
//variables
public: int _miPostition;
protected:
private:

//functions
public:
	Servo();
	Servo(int pos);
	void initTimer1PWM();
	void changeAngle(uint8_t angle);
	~Servo();
protected:
private:
	Servo( const Servo &c );
	Servo& operator=( const Servo &c );

}; //Servo

#endif //__SERVO_H__
