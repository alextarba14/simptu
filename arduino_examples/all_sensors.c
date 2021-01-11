//Libraries
#include <DHT.h>
#include <LiquidCrystal.h>

//Constants
#define DHTPIN 12     // attach pin D12 Arduino to out pin of DHT22
#define DHTTYPE DHT22   // DHT 22 (AM2302)
#define echoPin 11 // attach pin D11 Arduino to pin Echo of HC-SR04
#define trigPin 10 //attach pin D10 Arduino to pin Trig of HC-SR04

// LCD 
#define LCD_RS 9 // attach pin D9 Arduino to LCD RS
#define LCD_EN 8 // attach pin D8 Arduino to LCD E
#define LCD_D7 4 // attach pin D4 Arduino to LCD D7
#define LCD_D6 5 // attach pin D5 Arduino to LCD D6
#define LCD_D5 6 // attach pin D6 Arduino to LCD D5
#define LCD_D4 7 // attach pin D7 Arduino to LCD D4
#define LCD_ONOFF 3 // attach pin D3 Arduino to LCD A (15th pin)

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// keep the LCD enabled 5 seconds after 
// nothing was detected in front of HC-SR04
int lcd_on_delay = 0;
int lcd_on = false;

// defines variables for DHT22
float humidity;  //Stores humidity value
float temperature; //Stores temperature value

// HC-SR04 variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void turnOnLCD();
void turnOffLCD();
void printFirstLine();
void printSecondLine();

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
  dht.begin();
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(LCD_ONOFF,OUTPUT);
}

void loop(){   
    //Delay 1 second
    delay(1000); 

    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    distance = (duration * 0.034)/ 2; // Speed of sound wave divided by 2 (go and back)

    // Filtering interval and reading and displaying temperature
    // only when ultrasonic sensor detected something in front
    if(distance > 0 && distance < 200) {     
    // turning on lcd only when it's off
    if(!lcd_on){
		turnOnLCD();
    }
		//Read data and store it to variables humidity and temperature
		humidity = dht.readHumidity();
		temperature = dht.readTemperature();
    
		printFirstLine();
		printSecondLine();
    } else {
		// increasing number of seconds delayed after no presence was detected
		if(lcd_on_delay < 3){
			lcd_on_delay ++;
		} else{
			turnOffLCD();
		}
  }
}
void turnOnLCD(){
  // decreasing the backlight
  analogWrite(LCD_ONOFF,50);
  lcd_on_delay = 0; 
  lcd_on = true;
}

void turnOffLCD(){
  digitalWrite(LCD_ONOFF,LOW);  
  // clearing LCD when turning off
  lcd.clear();
  lcd_on = false;
}

void printFirstLine(){
  // Setting cursor on the first line
  lcd.setCursor(0,0);
  String message = String("T:");
  String tempString = removeLastCharacterFromString(String(temperature));
  String humString = removeLastCharacterFromString(String(humidity));
  message = message + tempString + "C, H:" + humString + "%";
  lcd.print(message); 
}

void printSecondLine(){
  // Setting cursor on the second line
  lcd.setCursor(0,1);
  String message = String("Dist: ");
  message = message + distance + "cm    ";
  lcd.print(message); 
}

String removeLastCharacterFromString(String message){
  message.remove(message.length()-1);
  return message;
}