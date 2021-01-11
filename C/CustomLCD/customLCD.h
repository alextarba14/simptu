#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>


//pins used to send data to LCD
#define   lcd_D7_ArdPin  PORTD4                 
#define   lcd_D6_ArdPin  PORTD5
#define   lcd_D5_ArdPin  PORTD6
#define   lcd_D4_ArdPin  PORTD7   
// pin used to command display ON_OFF
#define   LCD_ON_OFF     PORTD3
#define  lcd_E_ArdPin    PORTB0                
#define  lcd_RS_ArdPin   PORTB1                 

// LCD module information
#define lcd_LineOne     0x00                   
#define lcd_LineTwo     0x40                    

// LCD instructions
#define lcd_Clear           0b00000001          // replace all characters with ASCII 'space'
#define lcd_Home            0b00000010          // return cursor to first position on first line
#define lcd_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0b00001000          // turn display off
#define lcd_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0b00110000          // reset the LCD
#define lcd_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0b10000000          // set cursor position

// Function protopyes
void set_pins();
void turnOnLCD();
void turnOffLCD();
void lcd_init(void);
void lcd_write_string(uint8_t string[]);
void lcd_write_character(uint8_t  data);
void lcd_write_instruction(uint8_t  instruction);
void lcd_write(uint8_t  byte);
void lcd_clear();
void lcd_set_cursor(int row, int col);
void setupLcd();
void setTemperatureOnLcd(float temp);
void setHumidityOnLcd(float hum);
void setDistanceOnLcd(int dist);