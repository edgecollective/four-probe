#include <Arduino.h>
#include "Adafruit_ZeroTimer.h" // https://github.com/dwblair/Adafruit_ZeroTimer

// timer 3 ----------------------

float freq3 = 10000; // 10 Hz

volatile bool togglepin = false;
volatile bool togglepin2 = false;


int fourcounter = 0;

int timer3LED = 10;

int highswitchLED = 11;
int lowswitchLED = 12;

Adafruit_ZeroTimer zt3 = Adafruit_ZeroTimer(3);

void TC3_Handler(){
  Adafruit_ZeroTimer::timerHandler(3);
}



// timer 4 ----------------------

float freq4 = freq3*8; // 10 Hz


Adafruit_ZeroTimer zt4 = Adafruit_ZeroTimer(4);

void TC4_Handler(){
  Adafruit_ZeroTimer::timerHandler(4);
}


void Timer4Callback0()
{
  
//Serial.println(fourcounter);
if (fourcounter==0) {

    digitalWrite(timer3LED, HIGH);
digitalWrite(highswitchLED, LOW);
digitalWrite(lowswitchLED, LOW);

}

if (fourcounter==1) {

    digitalWrite(timer3LED, HIGH);
    digitalWrite(highswitchLED, LOW);
    digitalWrite(lowswitchLED, LOW);


}


if (fourcounter==2) {

    digitalWrite(timer3LED, HIGH);
    digitalWrite(highswitchLED, HIGH);
    digitalWrite(lowswitchLED, LOW);


}

else if (fourcounter==3) {

    digitalWrite(timer3LED, HIGH);
    digitalWrite(highswitchLED, LOW);
        digitalWrite(lowswitchLED, LOW);


}

else if (fourcounter==4) {

    digitalWrite(timer3LED, LOW);
        digitalWrite(highswitchLED, LOW);
        digitalWrite(lowswitchLED, LOW);

}


else if (fourcounter==5) {

        digitalWrite(highswitchLED, LOW);
    digitalWrite(lowswitchLED, LOW);
    digitalWrite(timer3LED, LOW);

}

else if (fourcounter==6) {

    digitalWrite(timer3LED, LOW);
     digitalWrite(highswitchLED, LOW);
    digitalWrite(lowswitchLED, HIGH);

}


else if (fourcounter==7) {

    digitalWrite(lowswitchLED, LOW);
    digitalWrite(timer3LED, LOW);
    digitalWrite(highswitchLED, LOW);

}


  fourcounter++;

if (fourcounter==8) {
  fourcounter=0;
}
  
  
}

void setup() {

  analogReadResolution(12);

  
  pinMode(timer3LED, OUTPUT);
  pinMode(highswitchLED, OUTPUT);
pinMode(lowswitchLED, OUTPUT);

  digitalWrite(highswitchLED, LOW);
    digitalWrite(lowswitchLED, LOW);
    
  Serial.begin(9600);
  //while (!Serial) {
   // delay(10);
  //}



  // for timer 4 ---------------------------------------

  
  //Serial.println("Timer callback tester");

  //Serial.print("Desired freq4 (Hz):");
  //Serial.println(freq4);

   // Set up the flexible divider/compare
  uint8_t divider  = 1;
  uint16_t compare = 0;
  tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;


  if ((freq4 < 24000000) && (freq4 > 800)) {
    divider = 1;
    prescaler = TC_CLOCK_PRESCALER_DIV1;
    compare = 48000000/freq4;
  } else if (freq4 > 400) {
    divider = 2;
    prescaler = TC_CLOCK_PRESCALER_DIV2;
    compare = (48000000/2)/freq4;
  } else if (freq4 > 200) {
    divider = 4;
    prescaler = TC_CLOCK_PRESCALER_DIV4;
    compare = (48000000/4)/freq4;
  } else if (freq4 > 100) {
    divider = 8;
    prescaler = TC_CLOCK_PRESCALER_DIV8;
    compare = (48000000/8)/freq4;
  } else if (freq4 > 50) {
    divider = 16;
    prescaler = TC_CLOCK_PRESCALER_DIV16;
    compare = (48000000/16)/freq4;
  } else if (freq4 > 12) {
    divider = 64;
    prescaler = TC_CLOCK_PRESCALER_DIV64;
    compare = (48000000/64)/freq4;
  } else if (freq4 > 3) {
    divider = 256;
    prescaler = TC_CLOCK_PRESCALER_DIV256;
    compare = (48000000/256)/freq4;
  } else if (freq4 >= 0.75) {
    divider = 1024;
    prescaler = TC_CLOCK_PRESCALER_DIV1024;
    compare = (48000000/1024)/freq4;
  } else {
    Serial.println("Invalid freq4uency");
    while (1) delay(10);
  }

  //Serial.println("Timer 4:");
 // Serial.print("Divider:"); Serial.println(divider);
 // Serial.print("Compare:"); Serial.println(compare);
 // Serial.print("Final freq4:"); Serial.println((int)(48000000/compare));

  zt4.enable(false);
  zt4.configure(prescaler,       // prescaler
          TC_COUNTER_SIZE_16BIT,       // bit width of timer/counter
          TC_WAVE_GENERATION_MATCH_PWM // freq3uency or PWM mode
          );

  zt4.setCompare(0, compare);
  zt4.setCallback(true, TC_CALLBACK_CC_CHANNEL0, Timer4Callback0);
  zt4.enable(true);

  
}

void loop() {

int numsamples = 100;
int sample_delay = 2; // milliseconds

float gain = 1000.;

 // V12B - V12C
 // 4p 6 - 4p 2
 // A3 - A4

 // V23B - V23C
 // 4p 1 - 4p 7
 // A5 - A2
 
 // TIB - TIC
// 4p 9 - 4 p 8
// A0 - A 1

float rsum = 0;
float tisum = 0;
float v23sum = 0;


for (int i=0;i<numsamples;i++) {
  

 int v12b = analogRead(A3);
 int v12c = analogRead(A4);

 int v23b = analogRead(A5);
 int v23c = analogRead(A2);

 int tib = analogRead(A0);
 int tic = analogRead(A1);

 float v12 = (float(v12c) - float(v12b))/4096.*3.3;

 float v23 = (float(v23c) - float(v23b))/4096.*3.3;
 float v23sum=v23sum+v23;
 

 float ti = (float(tic) - float(tib))/4096.*3.3;
 float tisum=tisum+ti;
 
 float r = float(v23)/float(ti)*gain;
 //Serial.println(r);

 rsum = rsum+r;
 
 delay(sample_delay);
 
}

float rave = rsum / float(numsamples);
float tiave = tisum / float(numsamples) * gain;
float v23ave = v23sum / float(numsamples);

//Serial.print(v23ave);
//Serial.print(",");
//Serial.print(tiave);
//Serial.print(",");
Serial.println(rave);

 /*
 Serial.print(v12);
 Serial.print(",");
 Serial.print(v23);
 Serial.print(",");
 Serial.print(ti);
 Serial.print(",");
 Serial.print(r);
 Serial.println();
 */
 
  delay(100);
}
