/* 
* SerialTxRx.cpp
*
* Created: 11.02.2016 10:28:49
* Author: Anton Shilin
*/


#include "SerialTxRx.h"


// default constructor
 SerialTxRx::SerialTxRx(uint16_t Baundrate)
 {
	this->UBRR_VALUE= (((F_CPU / (Baundrate * 16UL))) - 1); // Formula  Datasheet Page 203 Tabelle 22-1
}//SerialTxRx



 void SerialTxRx::Init_USART()
 {	
	/*in AVR GCC we can simply assign UBRR_VALUE value to UBRR0 
	OR UBRR0= UBRR_VALUE; 
	and leave to compiler to take care of writing sequence.
	*/
	UBRR0H = UBRR_VALUE>>8;
	UBRR0L = UBRR_VALUE;
	/*
	*****************Set frame****************************
	USART Mode: Asynchronous USART
	format: 8 DATA bits, NO parity, 1 STOP bit 
	USART Control and Status Register UCSR0C = 0b00000110 
	*******************************************************
	*/
	
	//enable transmission and reception
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	//enable global interrupts
	
}

unsigned char SerialTxRx::USART_receive(void)
{
	while((UCSR0A & (1<<RXC0))==0); // Prüfen ,ob bit RCX0 in UCSR0A gesetzt ist  
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