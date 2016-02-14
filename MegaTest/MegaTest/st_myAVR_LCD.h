 /*
* Created:				16/06/2013 17:22:15 
* Author:				Stevie Andrea Lucardi Version for Display	  16x2 on Atmega 8                                                
* modified by:			Anton Shilin          Version for Display	  16x4 on Atmega 2560   
* last modified at:		14.02.2016 
* Development Board:	Arduino Board Mega2560 R3                                            


 **************************PinOut Info for Arduino Board Mega 2560********************
 * LCD RS pin to digital 		Arduino pin 24 (PA2)
 * LCD Enable pin to digital 	Arduino pin 25 (PA3)
 * LCD D4 pin to digital 		Arduino pin 26 (PA4)
 * LCD D5 pin to digital 		Arduino pin 27 (PA5)
 * LCD D6 pin to digital 		Arduino pin 28 (PA6)
 * LCD D7 pin to digital 		Arduino pin 29 (PA7)
 * LCD R/W pin	to ground		Arduino GND
 * LCD VSS pin to ground		Arduino GND
 * LCD VCC(VDD) pin to 5V		Arduino 5V Out
 * LCD 15 Pin LED+				Arduino 5V Out
 * LCD 16 Pin LED-				Arduino GND
 * LCD VO (VEE) pin	to Poti(Contrast)		
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

#ifndef  st_myAVR_LCD
#define  st_myAVR_LCD

#ifndef  F_CPU
#warning F_CPU must be define.
#endif //F_CPU

#ifndef  _UTIL_DELAY_H_
#include <util/delay.h>
#endif //_UTIL_DELAY_H_

#include <avr/io.h>

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


////////////////////////////////////////////////////////////////////////////////
// Pinbelegung für das LCD, an verwendete Pins anpassen
// Alle LCD Pins müssen an einem Port angeschlossen sein und die 4
// Datenleitungen müssen auf aufeinanderfolgenden Pins liegen

#define LCD_DDR       DDRA
#define LCD_PORT      PORTA

//  LCD RS      <-->  PORTA Bit PA2     (RS: 1=Data, 0=Command)
#define LCD_RS        PA2
//  LCD EN      <-->  PORTA Bit PA3     (EN: 1-Impuls für Daten)
#define LCD_EN        PA3
//Erste DATAPORT
#define LCD_DB        PA4

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
#define LCD_DISPLAYCONTROL		0x08
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


void LCD_init(){
	LCD_DDR	|= 1 << LCD_RS;							// LCD_Pin 4   : RS (Register Select) 
	LCD_DDR	|= 1 << LCD_EN;							// LCD_Pin 6   : E  (ENABLE)
	LCD_DDR	|= 1 << LCD_D4;							// LCD_Pin 11  : D4 (Datenleitungen 4)
	LCD_DDR	|= 1 << LCD_D5;							// LCD_Pin 12  : D5 (Datenleitungen 5)
	LCD_DDR	|= 1 << LCD_D6;							// LCD_Pin 13  : D6 (Datenleitungen 6)
	LCD_DDR	|= 1 << LCD_D7;							// LCD_Pin 14  : D7 (Datenleitungen 7)

	// warten auf die Bereitschaft des LCD
	_delay_ms( LCD_BOOTUP_MS );
	
	// Soft-Reset muss 3mal hintereinander gesendet werden zur Initialisierung
	lcd_out( LCD_SOFT_RESET );
	_delay_ms( LCD_SOFT_RESET_MS1 );
	
	lcd_enable();
	_delay_ms( LCD_SOFT_RESET_MS2 );
	
	lcd_enable();
	_delay_ms( LCD_SOFT_RESET_MS3 );
	
	// 4-bit Modus aktivieren
	lcd_out( LCD_SET_FUNCTION |
			LCD_FUNCTION_4BIT );
	_delay_ms( LCD_SET_4BITMODE_MS );
	
	// 4-bit Modus / 2 Zeilen / 5x7
	lcd_command( LCD_SET_FUNCTION |
				LCD_FUNCTION_4BIT |
			   LCD_FUNCTION_2LINE |
				LCD_FUNCTION_5X7 );
	
	// Display ein / Cursor aus / Blinken aus
	lcd_command( LCD_SET_DISPLAY |
				 LCD_DISPLAY_ON  |
				 LCD_CURSOR_OFF  |
				 LCD_BLINKING_OFF);
	
	// Cursor inkrement / kein Scrollen
	lcd_command( LCD_SET_ENTRY |
			LCD_ENTRY_INCREASE |
			LCD_ENTRY_NOSHIFT );
	
	LCD_clr();
}

void lcd_data(uint8_t _dat){
 LCD_PORT |= (1<<LCD_RS);    // RS auf 1 setzen
 
 lcd_out( _dat );            // zuerst die oberen,
 lcd_out( _dat<<4 );         // dann die unteren 4 Bit senden
 
 _delay_us( LCD_WRITEDATA_US );
}


// Sendet einen Befehl an das LCD
void lcd_command(uint8_t _command){
	
	LCD_PORT &= ~(1<<LCD_RS);    // RS auf 0 setzen
	
	lcd_out( _command );             // zuerst die oberen,
	lcd_out( _command<<4 );           // dann die unteren 4 Bit senden
	
	_delay_us( LCD_COMMAND_US );
}

void LCD_clr(){
	lcd_command(0b00000001); 
	_delay_ms( LCD_CLEAR_DISPLAY_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Setzt den Cursor in Spalte x (0..15) Zeile y (0..3)
void LCD_gotoXY( uint8_t x, uint8_t y ){
 uint8_t data;

 switch (y)
 {
	 case 0:    // 1. Zeile
	 data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
	 break;
	 
	 case 1:    // 2. Zeile
	 data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
	 break;
	 
	 case 2:    // 3. Zeile
	 data = LCD_SET_DDADR + LCD_DDADR_LINE3 + x;
	 break;
	 
	 case 3:    // 4. Zeile
	 data = LCD_SET_DDADR + LCD_DDADR_LINE4 + x;
	 break;
	 
	 default:
	 return;                                   // Falls Falsche zeile eingegeben wird
 }
 
 lcd_command( data );
}

void LCD_printStr( char* str ){
	while( *str != 0 ) lcd_data( *str++ );
}

void LCD_printInt( const uint16_t value ){
	uint8_t length = 1;
	uint16_t div   = 10;
	
	while( value >= div ){
		div *= 10;
		length++;
	}
	
	if( length <= 1 ) lcd_data(' ');
	if( length <= 2 ) lcd_data(' ');
	if( length <= 3 ) lcd_data(' ');
	
	for( uint8_t i = length; i; i-- ){
		lcd_data( _toChar( (value%div)*10/div ) );
		div /= 10;
	}
}

void LCD_printInt( const uint8_t length, const uint16_t value ){
	uint8_t  len = 1;
	uint16_t div = 10;
	
	while( value >= div ){
		div *= 10;
		len++;
	}
	
	if( length > len )
		for( uint8_t i = length - len; i; i-- )
			lcd_data(' ');
	
	for( uint8_t i = len; i; i-- ){
		lcd_data( _toChar( (value%div)*10/div ) );
		div /= 10;
	}
}

uint8_t _toChar(uint8_t value){
	if ( value < 0 ) return 35;
	if ( value > 9 ) return 35;
	return value + 48;
}

////////////////////////////////////////////////////////////////////////////////
// Erzeugt einen Enable-Puls
void lcd_enable( void )
{
	LCD_PORT |= (1<<LCD_EN);     // Enable auf 1 setzen
	_delay_us( LCD_ENABLE_US );  // kurze Pause
	LCD_PORT &= ~(1<<LCD_EN);    // Enable auf 0 setzen
}

void lcd_out( uint8_t data )
{
	data &= 0xF0;                       // obere 4 Bit maskieren
	
	LCD_PORT &= ~(0xF0>>(4-LCD_DB));    // Maske löschen
	LCD_PORT |= (data>>(4-LCD_DB));     // Bits setzen
	lcd_enable();
}

#endif //st_myAVR_LCD