#include <CustomUltrasonic.h>

void setup() {
  Serial.begin(9600);

  init_ultrasonic();
}

void loop() {
  int distance = detectMotion();
  Serial.print("Distance:");
  Serial.println(distance);
  delay(500);
}
