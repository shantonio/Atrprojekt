/* 
* SerialTxRx.h
*
* Created: 11.02.2016 10:28:49
* Author: shantonio
*/


#ifndef __SERIALTXRX_H__
#define __SERIALTXRX_H__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>



/******************************Understanding USART data frames**************************************
USART communication uses special protocol to transmit data reliable. 
USART Control and Status Register  "UCSRC"
It consists of several parts:
- 1 START bit;

- 5,6,7,8 or 9 DATA bits;

- NO, EVEN, or ODD parity bit;

- 1 or 2 STOP bits.
*****************************************************************************************************/



class SerialTxRx
{
//variables
public:   unsigned char ReceivedByte;
protected:
private: uint8_t UBRR_VALUE;

//functions
public:
	
	SerialTxRx(uint16_t Baundrate);
	void Init_USART();
	unsigned char USART_receive(void);
	void USART_send(unsigned char data);
	void USART_putstring(char* StringPtr);
	~SerialTxRx();
protected:
private:
	SerialTxRx( const SerialTxRx &c );
	SerialTxRx& operator=( const SerialTxRx &c );

}; //SerialTxRx

#endif //__SERIALTXRX_H__
