#include <CustomLCD.h>
#include <CustomUltrasonic.h>

void setup(){
  set_pins();
  setupLcd();
  turnOnLCD();
  init_ultrasonic();
}

void loop(){  
   int distance = detectMotion();

   setTemperatureOnLcd(24.5);
   setHumidityOnLcd(49.4);
   setDistanceOnLcd(distance);
   _delay_ms(500);
}