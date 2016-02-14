/* 
* LcdDriver.cpp
*
* Created: 14.02.2016 22:17:37
* Author: Anton Shilin
*/


#include "LcdDriver.h"

// default constructor
LcdDriver::LcdDriver()
{
} //LcdDriver

// default destructor
LcdDriver::~LcdDriver()
{
} //~LcdDriver


void LcdDriver::LCD_init(){							//Hardware PIN : Symbol
	LCD_DDR	|= 1 << LCD_RS;							// LCD_Pin 4   : RS (Register Select)
	LCD_DDR	|= 1 << LCD_EN;							// LCD_Pin 6   : E  (ENABLE)
	LCD_DDR	|= 1 << LCD_D4;							// LCD_Pin 11  : D4 (Data 4)
	LCD_DDR	|= 1 << LCD_D5;							// LCD_Pin 12  : D5 (Data 5)
	LCD_DDR	|= 1 << LCD_D6;							// LCD_Pin 13  : D6 (Data 6)
	LCD_DDR	|= 1 << LCD_D7;							// LCD_Pin 14  : D7 (Data 7)

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

void LcdDriver::lcd_data(uint8_t _dat){
	LCD_PORT |= (1<<LCD_RS);    // RS auf 1 setzen
	
	lcd_out( _dat );            // zuerst die oberen,
	lcd_out( _dat<<4 );         // dann die unteren 4 Bit senden
	
	_delay_us( LCD_WRITEDATA_US );
}


// Sendet einen Befehl an das LCD
void LcdDriver::lcd_command(uint8_t _command){
	
	LCD_PORT &= ~(1<<LCD_RS);			 // RS auf 0 setzen
	
	lcd_out( _command );				 // zuerst die oberen,
	lcd_out( _command<<4 );				 // dann die unteren 4 Bit senden
	
	_delay_us( LCD_COMMAND_US );
}

void LcdDriver::LCD_clr(){
	lcd_command(0b00000001);
	_delay_ms( LCD_CLEAR_DISPLAY_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Setzt den Cursor in Spalte x (0..15) Zeile y (0..3)
void LcdDriver::LCD_gotoXY( uint8_t x, uint8_t y ){
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

void LcdDriver::LCD_printStr( char* str ){
	while( *str != 0 ) lcd_data( *str++ );
}

void LcdDriver::LCD_printInt( const uint16_t value ){
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

void LcdDriver::LCD_printInt( const uint8_t length, const uint16_t value ){
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

uint8_t LcdDriver::_toChar(uint8_t value){
	if ( value < 0 ) return 35;
	if ( value > 9 ) return 35;
	return value + 48;
}

////////////////////////////////////////////////////////////////////////////////
// Erzeugt einen Enable-Puls
void LcdDriver::lcd_enable( void )
{
	LCD_PORT |= (1<<LCD_EN);     // Enable auf 1 setzen
	_delay_us( LCD_ENABLE_US );  // kurze Pause
	LCD_PORT &= ~(1<<LCD_EN);    // Enable auf 0 setzen
}

void LcdDriver::lcd_out( uint8_t data )
{
	data &= 0xF0;                       // obere 4 Bit maskieren
	
	LCD_PORT &= ~(0xF0>>(4-LCD_DB));    // Maske löschen
	LCD_PORT |= (data>>(4-LCD_DB));     // Bits setzen
	lcd_enable();
}
