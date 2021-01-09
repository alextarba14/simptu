//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 12     // attach pin D12 Arduino to out pin of DHT22
#define DHTTYPE DHT22   // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// defines variables
float humidity;  //Stores humidity value
float temperature; //Stores temperature value

void setup()
{
  Serial.begin(9600);
  dht.begin();
}

void loop(){   
  
    //Delay 5 seconds
    delay(5000); 
    
    //Read data and store it to variables hum and temp
    humidity = dht.readHumidity();
    temperature= dht.readTemperature();
    
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %, Temp: ");
    Serial.print(temperature);
    Serial.println(" Celsius");
    
}
