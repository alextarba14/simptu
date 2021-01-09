// include the library code:
#include <LiquidCrystal.h>

// Constants
#define LCD_RS 9 // attach pin D9 Arduino to LCD RS
#define LCD_EN 8 // attach pin D8 Arduino to LCD E
#define LCD_D7 4 // attach pin D4 Arduino to LCD D7
#define LCD_D6 5 // attach pin D5 Arduino to LCD D6
#define LCD_D5 6 // attach pin D6 Arduino to LCD D5
#define LCD_D4 7 // attach pin D7 Arduino to LCD D4
#define LCD_ONOFF 3 // attach pin D3 Arduino to LCD A (15th pin)

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
int on = true;
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  pinMode(LCD_ONOFF,OUTPUT);
}

void loop() {
  delay(5000);
  if(on){
    digitalWrite(LCD_ONOFF,LOW);
    on = false;
  } else{
    digitalWrite(LCD_ONOFF,HIGH);
    on = true;
  }
}

