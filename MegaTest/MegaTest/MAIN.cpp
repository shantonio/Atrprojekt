/*
 * mega2560.c
 *
 * Created: 28.07.2015 00:08:28
 *  Author: shantonio
 */ 

#ifndef F_CPU
#define F_CPU 16000000
#endif


#include <avr/interrupt.h>
#include <util/delay.h>


#include "Servo.h"
#include "SerialTxRx.h"
#include "LcdDriver.h"
#include "st_button.h"


int extraTime = 0;
int extraTime1 = 0;
int in=1;
 
char teststr0[8]="Servo1:";
char teststr1[8]="Servo2:";
char startMesage[12]="Info Blatt";
char *teststr;
uint16_t winkel=0;
unsigned char u8TempData=0;

SerialTxRx print(9600);
    
LcdDriver *display;
#define AddressPort 0x2C-__SFR_OFFSET

  
//void initTimer0()							// 8 Bit Timer
//{
//DDRB |= (1<<PORTB7);						//Nur für LED TEST Arduino PIN13;
//TCCR0A = (1 << WGM01);						// Set CTC MODE Bit 
////TIMSK0 = (1 << OCIE0A);					// Set Timer Interrupt Mask 
//sbi(TIMSK0,OCIE0A);							// Genau das gleiche nur mit Macro sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
//TCCR0B |= (1 << CS02) | (1 << CS00);		// Clock prescalar at 1024 
//sei();										// Set I-Bit in status register (SREG).
//OCR0A = 16;									// For 1ms Output Compare Register 
//}

void initTimer1(){						// 16 Bit Timer
	 DDRB |= (1<<PB4);			// 
	TCCR1B |= (1 << WGM12)|(1 << CS12) | (1 << CS10);	//prescalar at 1024 and Set CTC MODE siehe datenBlatt 
	sei();												// Set I-Bit in status register (SREG).
	OCR1A = 156;										// For 10ms Output Compare Register 
	TIMSK1 = (1 << OCIE1A);								// Set Timer Interrupt Mask
		 									
}
     ///
  
int main(void)
{	 // DDRB |= (1<<PB7); // LED ON/OFF Arduino PIN 13 // PinMODE OUTPUT
	//Servo servo1_2(90);
	//1servo1_2.initTimer1PWM();
	
	//Button scanOrAbort(&PORTE, PINE4, true);
	//Button lcdButton(&PORTE, PINE5 , true);
	 
	//initTimer0();
	//display->LCD_init();
	//display->LCD_clr();
	
	//initTimer1();
	print.Init_USART();
		//strcat (Servo0,Servo1);
		//strcat (Servo0,"\n");

	
	  
	 
		//display->LCD_gotoXY(0,3);
		//_delay_ms(100);
		//display->LCD_printStr(startMesage);
		//_delay_ms(100);
		 /*
		display->LCD_gotoXY(1,1);
		_delay_ms(100);
		display->LCD_printStr(teststr1);
		_delay_ms(1000);
		
		display->LCD_gotoXY(2,2);
		_delay_ms(100);
		display->LCD_printStr(teststr2);
		_delay_ms(1000);
		
			display->LCD_gotoXY(3,3);
			_delay_ms(100);
			display->LCD_printStr(teststr3);
			_delay_ms(1000);

  */
	
	
	
	while(1)
	{ 
  //////////// LCD AND SERVO CHECK mit USART	*************************************      
		//servo1_2.changeAngle(winkel);
		//char* temp=print.AngleToServo(1,winkel);
		//if(print.USART_isReceived())
		//print.USART_putstring(temp);
		_delay_ms(15);
		
		winkel=winkel+in;
		if (winkel>=180||winkel<=0) {
			in=in*(-1);
			}
//display->LCD_gotoXY(0,0);
//_delay_ms(5);
//display->LCD_printStr(teststr0);
//display->LCD_printInt(winkel);

//display->LCD_gotoXY(0,1);
//_delay_ms(5);
//display->LCD_printStr(teststr1);
//display->LCD_printInt(winkel);		  

if(print.USART_isReceived())
{
	
	
	print.USART_putstring(teststr0);
	print.USART_putstring(print.AngleToServo(1,winkel));
	
}
	
 
/*
      // *******************BUTTONS TEST *********************************************
scanOrAbort.Check();        //< Instruct the button to check the pin
if(scanOrAbort.IsPressed()) //< Check the state of the button
{
	winkel++;
	 
}

	lcdButton.Check();        //< Instruct the button to check the pin
	if(lcdButton.IsPressed()) //< Check the state of the button
	{
	winkel--;}

	display->LCD_gotoXY(0,0);
	_delay_ms(5);
	display->LCD_printStr(teststr0);
	display->LCD_printInt(winkel);
	_delay_ms(5);
		}
*///END BUTTON TEST

	}
}
/*
ISR(TIMER0_COMPA_vect)
{
	extraTime++;
	
	if(extraTime >= 1000)
	{
		extraTime = 0;
		PORTB ^= (1 << PORTB7);   //Toggle Port
		
		//if(PORTB!=1 << PORTB5)
		//PORTB |= (1 << PORTB5);
		//else PORTB &= ~(1 << PORTB5);
		
	}
}	// END OF Interrupt Timer0
*/

ISR(TIMER1_COMPA_vect)    
{
	extraTime1++;
	
	if(extraTime1 >= 100){
		extraTime1 = 0;
	//Toggle Port;
		PORTB ^= (1 << PORTB7);   // Test Interrupt Timer1 LED ON/OFF Arduino PIN13
		}
}	// END OF Interrupt Timer1 






