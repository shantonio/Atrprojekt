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
#include <stdlib.h>
#include <string.h>


#include "Servo.h"
#include "SerialTxRx.h"
#include "LcdDriver.h"


int extraTime = 0;
int extraTime1 = 0;
char winkel[3];

char Servo0[10];    //String[] is in fact an array but when we put the text between the " " symbols the compiler threats it as a String and automatically puts the null termination character in the end of the text
char Servo1[10];
char teststr0[5]="x0y0";
char teststr1[5]="x1y1";
char teststr2[5]="x2y2";
char teststr3[5]="x3y3";
uint16_t cZahl=0;
unsigned char u8TempData=0;

SerialTxRx print(9600);
LcdDriver *display;
  
//void initTimer0()							//  8 Bit Timer
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


int main(void)
{	  DDRB |= (1<<PB7); // LED ON/OFF Arduino PIN 13 // PinMODE OUTPUT
	//Servo servo1_2(90);
	//servo1_2.initTimer1PWM();
	
	//initTimer0();
	display->LCD_init();
	display->LCD_clr();
	
	//initTimer1();
	//print.Init_USART();
		//strcat (Servo0,Servo1);
		//strcat (Servo0,"\n");

	//print.USART_putstring(Servo1);
	
	  
		display->LCD_gotoXY(0,0);
		_delay_ms(100);
		display->LCD_printStr(teststr0);
		_delay_ms(1000);
		
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


	cZahl = 100;
	
	
	while(1)
	{
	
		
		//u8TempData = print.USART_receive(); // Wenn nix eingegebn dann warter er in funktion
		//u8TempData++;
		//print.USART_send(u8TempData);
		//print.USART_send('\n');
	
	/*
		strcpy (Servo0,"S0:");
		itoa(cZahl,winkel,10);
		strcat (Servo0,winkel);
		strcat (Servo0,"\n");
		cZahl=cZahl+1;
		print.USART_putstring(Servo0);
		_delay_ms(100);
		strcpy (Servo1,"S1:");
		itoa(cZahl+2,winkel,10);
		strcat (Servo1,winkel);
		strcat (Servo1,"\n");
		cZahl=cZahl+1;
		print.USART_putstring(Servo1);
		_delay_ms(100);
		
		*/	
			
		

	}
//servo1_2.~Servo();
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






