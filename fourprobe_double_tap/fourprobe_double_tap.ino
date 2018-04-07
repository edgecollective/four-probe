// ref: https://www.sparkfun.com/news/2613


// Pins
const int led_pin = PB5; // PB5 (pin 13)
const int led_pin_2 = PB4; //  PB4 (pin 12)

// Counter and compare values
uint16_t toggle = 0;
const uint16_t t1_load = 0;
const uint16_t t1_comp = 2000; // max 31250
const uint16_t t1_buff = 1000; // amount of ticks before endpoint to sample

void setup() {

  // Set LED pin to be output
  DDRB |= (1 << led_pin);
  DDRB |= (1 << led_pin_2);

  // Reset Timer1 Control Reg A
  TCCR1A = 0;

  // Set to prescaler of 256
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  // Reset Timer1 and set compare value
  TCNT1 = t1_load;
  OCR1A = t1_comp;

  // Enable Timer1 overflow interrupt
  TIMSK1 = (1 << OCIE1A);

  // Enable global interrupts
  sei();
  Serial.begin(9600);
}

void loop() {
  delay(500);
  
}

ISR(TIMER1_COMPA_vect) {
  if (toggle == 0) { 
    TCNT1 = t1_comp - t1_buff;
    //Serial.print("toggle 0; TCNT1=");
    //Serial.println(TCNT1);
    toggle = 1;
    PORTB ^= (1 << led_pin_2);
  }
  else if (toggle == 1) {
    TCNT1 = t1_load;
    //Serial.print("toggle 1; TCNT1=");
    //Serial.println(TCNT1);
    toggle = 0;
    PORTB ^= (1 << led_pin);
  }
  
}
