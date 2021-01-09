//Libraries
#include <DHT.h>

//Constants
#define DHTPIN 12     // attach pin D12 Arduino to out pin of DHT22
#define DHTTYPE DHT22   // DHT 22 (AM2302)
#define echoPin 11 // attach pin D11 Arduino to pin Echo of HC-SR04
#define trigPin 10 //attach pin D10 Arduino to pin Trig of HC-SR04


DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

// defines variables for DHT22
float humidity;  //Stores humidity value
float temperature; //Stores temperature value

// HC-SR04 variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600);
  dht.begin();
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
      // Displays the distance on the Serial Monitor
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
      
      //Read data and store it to variables humidity and temperature
      humidity = dht.readHumidity();
      temperature= dht.readTemperature();
    
      //Print temp and humidity values to serial monitor
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print(" %, Temp: ");
      Serial.print(temperature);
      Serial.println(" Celsius");
    }   
}
