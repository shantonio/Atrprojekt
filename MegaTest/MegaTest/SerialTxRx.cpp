/* 
* SerialTxRx.cpp
*
* Created: 11.02.2016 10:28:49
* Author: Anton Shilin
*/


#include "SerialTxRx.h"
#include <util/delay.h>
char Servo[8]; // Tempvariable

// default constructor
 SerialTxRx::SerialTxRx(uint16_t Baundrate)
{
	this->UBRR_VALUE= (((F_CPU / (Baundrate * 16UL))) - 1); 
}//SerialTxRx



 void SerialTxRx::Init_USART()
 {	
	/* 
	 * in AVR GCC we can simply assign UBRR_VALUE value to UBRR0 
	 * and leave to compiler to take care of writing sequence.
	*/
	//UBRR0H = UBRR_VALUE>>8;
	//UBRR0L = UBRR_VALUE;
	UBRR0= UBRR_VALUE;
	/*
	*****************Set frame****************************
	USART Mode: Asynchronous USART
	FORMAT: 8 DATA bits, NO parity, 1 STOP bit 
	USART Control and Status Register UCSR0C = 0b00000110 
	*******************************************************
	*/
	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00)|(0<<UMSEL00);
	
	
}


bool SerialTxRx::USART_available(void)
{
	return (UCSR0A & (1<<RXC0))!=0;
}

 
 bool SerialTxRx::USART_isReceived(void)
{
	if(USART_available())
	{ 	while(USART_available())
		{
		ReceivedByte= UDR0;
		_delay_ms(2);
		}
	return true;
	}
	return false;
}


unsigned char SerialTxRx::USART_receive(void)
{
	while((UCSR0A & (1<<RXC0))==0); //!! Prüfen ,ob bit RCX0 in UCSR0A gesetzt ist !! 
	// Do nothing until data have been received and is ready to be read from UDR (warten bis Zeichen verfuegbar)
	ReceivedByte= UDR0;
	return ReceivedByte;
}

void SerialTxRx::USART_send(unsigned char data)
 {
	  while((UCSR0A & (1<<UDRE0))==0);
	   // Do nothing until UDR is ready for more data to be written to it
	 UDR0 = data;
 }

void SerialTxRx::USART_putstring(char* StringPtr)
{
		while(*StringPtr != 0x00){
		USART_send(*StringPtr);
		StringPtr++;
		}
}

// default destructor
SerialTxRx::~SerialTxRx()
{} //~SerialTxRx

char *SerialTxRx::AngleToServo(uint8_t _ServoNumber,uint16_t _Angle)
{
	char angleBuffer[3];
	
	//memset(Servo, '\0', sizeof(Servo));
	
	if (_ServoNumber==0){
		strcpy (Servo,"S0:");
		itoa(_Angle,angleBuffer,10);
		strcat (Servo,angleBuffer);
		strcat (Servo,"\n");
	}

	if (_ServoNumber==1){
			strcpy (Servo,"S1:");
			itoa(_Angle,angleBuffer,10);
			strcat (Servo,angleBuffer);
			strcat (Servo,"\n");
	}
	
	return Servo;
}
