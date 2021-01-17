#include "CustomUltrasonic.h"

volatile unsigned int counter;

ISR(INT1_vect)
{
  if(PIND & (1 << ECHO_PIN)){
      // reset timer on HIGH input signal
      TCNT1 = 0;
   }else{
      // on LOW input signal store the HIGH period of signal
      counter = TCNT1;
   }
}

int detectMotion(){
  counter = 0;
  // set Trig_Pin on HIGH
  PORTD |=  (1 << TRIG_PIN);
  // wait 10us in order to generate a signal with 10us period on HIGH
  _delay_us(10);
  // set Trig_Pin on LOW
  PORTD &= ~(1 << TRIG_PIN);

  // wait for echo
  while(counter == 0);

  // since we get an increment at each 4us
  // we must multiply again with 4 in order to have
  // the period in correct us form 
  // then divide it by 58 to get the value in cm.
  return (counter * 4)/58;
}

void init_ultrasonic(){
    // setting pin 2 as output
  DDRD |= (1<<TRIG_PIN);
  
  EIMSK |= (1<<INT1); 
  EICRA |= (1<<ISC10);
  sei();
  
  TCNT1 = 0x0000; // clear Timer1 current value
  TCCR1A = 0x00;  // 
  TCCR1B = (1<<CS11) | (1<<CS10); //clkI/O / 64 -> 4us for each increment
}