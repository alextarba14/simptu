#include "customLCD.h"


// Set Arduino pins as output for communication with LCD
void set_pins(){
  DDRD |=   (1<<lcd_D7_ArdPin) |
      		(1<<lcd_D6_ArdPin) |
      		(1<<lcd_D5_ArdPin) |
     		(1<<lcd_D4_ArdPin) |
    		(1<<LCD_ON_OFF);
  
  DDRB |=	(1<<lcd_E_ArdPin) |
    		(1<<lcd_RS_ArdPin);	
}

void turnOnLCD(){
  PORTD |= (1<<LCD_ON_OFF);
}

void turnOffLCD(){
  PORTD = (PORTD & (~(1<<LCD_ON_OFF)));
}

// Executes a set of commands in order to setup LCD, see LCD 1602 datasheet for more
void lcd_init(void)
{
    _delay_ms(100);                               

    lcd_write(lcd_FunctionReset);                
    _delay_ms(10);                                 

    lcd_write(lcd_FunctionReset);                
    _delay_us(200);                                

    lcd_write(lcd_FunctionReset);                 
    _delay_us(200);                               
 
    lcd_write(lcd_FunctionSet4bit);             
    _delay_us(80);                                  

    lcd_write_instruction(lcd_FunctionSet4bit);   
    _delay_us(80);                                  

    lcd_write_instruction(lcd_DisplayOff);        
    _delay_us(80);                                  

    lcd_write_instruction(lcd_Clear);          
    _delay_ms(4);                                 

    lcd_write_instruction(lcd_EntryMode);       
    _delay_us(80);                              

    lcd_write_instruction(lcd_DisplayOn);         
    _delay_us(80);   
  
  // keep the lcd alive for 10 seconds
  // then turn off
  turnOnLCD();
}

// Takes a string as input and writes characters to LCD one by one
void lcd_write_string(uint8_t string[])
{
    volatile int i = 0;                             
    while (string[i] != 0)
    {
        lcd_write_character(string[i]);
        i++;
        _delay_us(80);                        
    }
}

/*
Writes a character to LCD given as input
RS should be HIGH
E should be LOW
8 bit data input is sent in two steps of 4 bits
NOTE: lcd_write function accepts 4-bit input to minimize amount of used pins/wires
*/
void lcd_write_character(uint8_t  data)
{
    PORTB |= (1<<lcd_RS_ArdPin);
    PORTB &= ~(1<<lcd_E_ArdPin);
    lcd_write(data);
  	lcd_write(data<<4); 
}

/*
Writes an instruction to LCD given as input
RS should be LOW
E should be LOW
8 bit instruction input is sent in two steps of 4 bits
NOTE: lcd_write function accepts 4-bit input to minimize amount of used pins/wires
*/
void lcd_write_instruction(uint8_t  instruction)
{
    PORTB &= ~(1<<lcd_RS_ArdPin);
    PORTB &= ~(1<<lcd_E_ArdPin);               
    lcd_write(instruction);
  	lcd_write(instruction<<4);  
}

/*
Sends the upper 4 bits of parameter to LCD one by one
At the end E should be HIGH for 1us to trigger sending.
*/
void lcd_write(uint8_t  byte)
{
    PORTD &= ~(1<<lcd_D7_ArdPin);                      
    if (byte & 1<<7) PORTD |= (1<<lcd_D7_ArdPin);  
          
    PORTD &= ~(1<<lcd_D6_ArdPin);                       
    if (byte & 1<<6) PORTD |= (1<<lcd_D6_ArdPin);    

    PORTD &= ~(1<<lcd_D5_ArdPin);
    if (byte & 1<<5) PORTD |= (1<<lcd_D5_ArdPin);

    PORTD &= ~(1<<lcd_D4_ArdPin);
    if (byte & 1<<4) PORTD |= (1<<lcd_D4_ArdPin);
    
                                                   
    PORTB |= (1<<lcd_E_ArdPin);             
    _delay_us(1);                          
    PORTB &= ~(1<<lcd_E_ArdPin);             
    _delay_us(1);                          
}

// Sends an instruction to LCD for clear
void lcd_clear(){
	lcd_write_instruction(lcd_Clear);
	_delay_ms(4);  
}

// Helper function to set LCD cursor 
void lcd_set_cursor(int row, int col){
	if(row == 1 && col <= 16){
	  lcd_write_instruction(lcd_SetCursor | lcd_LineOne + col - 1);
	  _delay_us(80);  
	}else if(row == 2 && col <= 16){
	  lcd_write_instruction(lcd_SetCursor | lcd_LineTwo + col - 1);
	  _delay_us(80);  
	}else{
	  return;
	}
} 

// Writes two strings on LCD
void setupLcd(){
   uint8_t temperature_humidity_label[]   = "T:    C H:    %";
   uint8_t distance_label[]="Dist: ";
   lcd_init();  
   lcd_set_cursor(1,1);
   lcd_write_string(temperature_humidity_label);
   lcd_set_cursor(2,1);
   lcd_write_string(distance_label);
}

// Writes float number to LCD, firstly converts it to a string 
void setTemperatureOnLcd(float temp){
  char temp_str[4];
  dtostrf(temp,3,1,temp_str);
  lcd_set_cursor(1,3);
  lcd_write_string((uint8_t*)temp_str);
}

// Writes float number to LCD, firstly converts it to a string 
void setHumidityOnLcd(float hum){
  char hum_str[3];
  dtostrf(hum,3,1,hum_str);
  lcd_set_cursor(1,11);
  lcd_write_string((uint8_t*)hum_str);
}

// Writes int number to LCD, firstly converts it to a string
void setDistanceOnLcd(int dist){
  /* Calculate length for distance string
  	 Display values range 2-100cm means 1,2 or 3 digits */
  int length = 0;
  if(dist < 10){
  	length = 1;
  }else if(dist < 100){
   	length = 2; 
  }else{
   	length = 3; 
  }
  
  char dist_str[length];
  dtostrf(dist,length,0,dist_str);
  lcd_set_cursor(2,7);
  lcd_write_string((uint8_t*)dist_str);
  lcd_write_string((uint8_t*)"cm");
}