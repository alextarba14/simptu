#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define TRIG_PIN 2
#define ECHO_PIN 3

int detectMotion();
void init_ultrasonic();