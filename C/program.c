#include <CustomLCD.h>
#include <CustomUltrasonic.h>
#include <DHT.h>

//Constants
#define DHTPIN 12     // attach pin D12 Arduino to out pin of DHT22
#define DHTTYPE DHT22   // DHT 22 (AM2302)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);
// defines variables for DHT22
float humidity;  //Stores humidity value
float temperature; //Stores temperature value

// keep the LCD enabled 2 seconds after 
// nothing was detected in front of HC-SR04
int lcd_on_delay = 0;
int lcd_on = false;

void setup(){
  // Init LCD
  set_pins();
  setupLcd();
  
  init_ultrasonic();
}

void loop(){  
   int distance = detectMotion();

   // Filtering interval and reading and displaying temperature
   // only when ultrasonic sensor detected something in front
   if(distance > 2 && distance < 200) {     
      // turning on lcd only when it's off
      if(!lcd_on){
        lcd_on_delay = 0; 
        lcd_on = true;
        turnOnLCD();
      }
      //Read data and store it to variables humidity and temperature
      humidity = dht.readHumidity();
      temperature = dht.readTemperature();

      setTemperatureOnLcd(temperature);
      setHumidityOnLcd(humidity);
      setDistanceOnLcd(distance);
    } else {
      // increasing number of seconds delayed after no presence was detected
      if(lcd_on_delay < 2){
        lcd_on_delay ++;
      } else{
        lcd_on = false;
        turnOffLCD();
      }
  }

    
   // Delay half a second
   _delay_ms(500);
}