/* 
* LcdDriver.h
*
*
* Created:				"st_myAVR_LCD.h" 16/06/2013 17:22:15 
* Author:				Stevie Andrea Lucardi Version for Display	  16x2 on Atmega 8                                                
* modified by:			Anton Shilin          Version for Display	  16x4 on Atmega 2560   
* last modified at:		14.02.2016 22:17:37
* Development Board:	Arduino Board Mega2560 R3                                            


 **************************PinOut Info for Arduino Board Mega 2560********************
 * LCD VSS			pin 1 to ground			Arduino pin GND
 * LCD VCC(VDD)		pin 2 to 5V				Arduino pin 5V Out
 * LCD VO (VEE)		pin	3					Poti    (Contrast)	
 * LCD RS			pin 4  to digital 		Arduino pin 24 (PA2)
 * LCD R/W			pin	5  to ground		Arduino pin GND
 * LCD E(Enable)	pin 6  to digital 		Arduino pin 25 (PA3)
 * LCD D4			pin 11 to digital 		Arduino pin 26 (PA4)
 * LCD D5			pin 12 to digital 		Arduino pin 27 (PA5)
 * LCD D6			pin 13 to digital 		Arduino pin 28 (PA6)
 * LCD D7			pin 14 to digital 		Arduino pin 29 (PA7)
 * LCD LED+			pin 15 					Arduino pin 5V Out
 * LCD LED-			pin 16					Arduino pin GND
	
 */


/** Functions :

	void		LCD_init()														// initialize LCD
	void		LCD_clr()														// clear LCD
	void		LCD_gotoXY				( uint8_t x, uint8_t y )				// set DDRAM address
	void		LCD_printStr			( char* str )							// print string
	void		LCD_printInt			( const uint16_t value )				// print numerical value
	void		lcd_data				( uint8_t _dat )						// send data
	void		lcd_command				( uint8_t command )						// send command
	uint8_t		_toChar					( uint8_t value )						// convert numerical value into ASCII code

**/


#ifndef __LCDDRIVER_H__
#define __LCDDRIVER_H__

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef  _UTIL_DELAY_H_
#include <util/delay.h>
#endif //_UTIL_DELAY_H_

#include <avr/io.h>


////////////////////////////////////////////////////////////////////////////////
// Pinbelegung für das LCD, an verwendete Pins anpassen
// Alle LCD Pins müssen an einem Port angeschlossen sein und die 4
// Datenleitungen müssen auf aufeinanderfolgenden Pins liegen

#define LCD_DDR       DDRA
#define LCD_PORT      PORTA
//n=A;
//  LCD RS      <-->  PORTn Bit Pn2     (RS: 1=Data, 0=Command)
#define LCD_RS        PA2
//  LCD EN      <-->  PORTn Bit Pn3     (EN: 1-Impuls für Daten)
#define LCD_EN        PA3
//First Data Bit Pin 
#define LCD_DB        PA4
//Data Pins 
#define LCD_D4        PA4
#define LCD_D5        PA5
#define LCD_D6        PA6
#define LCD_D7        PA7


////////////////////////////////////////////////////////////////////////////////
// LCD Ausführungszeiten (MS=Millisekunden, US=Mikrosekunden)

#define LCD_BOOTUP_MS           15
#define LCD_ENABLE_US           20
#define LCD_WRITEDATA_US        46
#define LCD_COMMAND_US          42

#define LCD_SOFT_RESET_MS1      5
#define LCD_SOFT_RESET_MS2      1
#define LCD_SOFT_RESET_MS3      1
#define LCD_SET_4BITMODE_MS     5
#define LCD_CLEAR_DISPLAY_MS    2


// Set Function --------------- 0b001xxxxx
#define LCD_SET_FUNCTION        0x20
#define LCD_FUNCTION_4BIT       0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_2LINE      0x08
#define LCD_FUNCTION_5X7        0x00

#define LCD_SOFT_RESET          0x30

// Set Display ---------------- 0b00001xxx
#define LCD_SET_DISPLAY         0x08
#define LCD_DISPLAY_OFF         0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_CURSOR_ON           0x02
#define LCD_BLINKING_OFF        0x00
#define LCD_BLINKING_ON         0x01

// Set Entry Mode ------------- 0b000001xx
#define LCD_SET_ENTRY           0x04
#define LCD_ENTRY_DECREASE      0x00
#define LCD_ENTRY_INCREASE      0x02
#define LCD_ENTRY_NOSHIFT       0x00
#define LCD_ENTRY_SHIFT         0x01

////////////////////////////////////////////////////////////////////////////////
// Zeilendefinitionen des verwendeten LCD
// Die Einträge hier sollten für ein LCD mit einer Zeilenlänge von 16 Zeichen passen
// Bei anderen Zeilenlängen müssen diese Einträge angepasst werden

#define LCD_DDADR_LINE1         0x00
#define LCD_DDADR_LINE2         0x40
#define LCD_DDADR_LINE3         0x10
#define LCD_DDADR_LINE4         0x50

// Set DD RAM Address --------- 0b1xxxxxxx  (Display Data RAM)
#define LCD_SET_DDADR           0x80



class LcdDriver
{
//variables
public:
private:

//functions
public:
	LcdDriver();
	~LcdDriver();
	void LCD_init();
void LCD_clr();
void LCD_gotoXY( uint8_t x, uint8_t y );
void LCD_printStr( char* str );
void LCD_printInt( const uint16_t value );
void LCD_printInt( const uint8_t length, const uint16_t value );

void lcd_enable( void );
void lcd_out( uint8_t data );
void lcd_data( uint8_t _dat );
void lcd_command( uint8_t _cmd );
uint8_t _toChar( uint8_t value );


private:
	LcdDriver( const LcdDriver &c );
	LcdDriver& operator=( const LcdDriver &c );

}; //LcdDriver

#endif //__LCDDRIVER_H__
