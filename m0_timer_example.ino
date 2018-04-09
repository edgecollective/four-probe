


/////////////////////////////////////////////////////////////////////////
//
//
//   Real time clock on TC3
//
//
//
/////////////////////////////////////////////////////////////////////////

volatile uint32_t realTcount = 0x0 ;   // Counter for superticks (overflow interrupts)


void setup() {
Serial.begin(9600);
setTC3clock();
}


/*
This is test code that counts to 10 s then resets and waits 3s to test 
reset, start and stop functions on TC3. 
*/
void loop() {
  
  delay(250);
  
    Serial.print(realTime(), 7);
    Serial.println();
    double val = realTime();
   
    if( int(val) >= 10)
    {
  resetStartTC3();  // reset so never gets above 10 s
      stopTC3();
    delay(3000); //wait 3 sec
    startTC3();
    }
    
}





void TC3_Handler()  // Interrupt on overflow
{
  TcCount16* TC = (TcCount16*) TC3; // get timer struct
    realTcount++;                    // Increment the supertick register
    TC->INTFLAG.bit.OVF = 1;    // writing a one clears the ovf flag
//  }
}

/*
Get the real time in seconds.
*/
double realTime() 
{   
double  realTime =  (realTcount * 1.2288E-2) + (REG_TC3_COUNT16_COUNT * 1.875E-7) ;;
return realTime;
}


/*
  Setup the Generic clock register
*/


void setTC3clock()
{
  GCLK->CLKCTRL.reg = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID( GCM_TCC2_TC3 ));
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization
  TcCount16* TC = (TcCount16*) TC3; // get timer struct
  TC->CTRLA.reg &= ~TC_CTRLA_ENABLE;   // Disable TC
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;  // Set Timer counter Mode to 16 bits
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  TC->CTRLA.reg |= TC_CTRLA_WAVEGEN_NFRQ; // Set TC as normal Normal Frq
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV8;   // Set perscaler
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  // Interrupts
  TC->INTENSET.reg = 0;              // disable all interrupts
  TC->INTENSET.bit.OVF = 1;          // enable overfollow interrup
  // Enable InterruptVector
  NVIC_EnableIRQ(TC3_IRQn);
  // Enable TC
  TC->CTRLA.reg |= TC_CTRLA_ENABLE;
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
}



void resetStartTC3()
{
   TcCount16* TC = (TcCount16*) TC3; // get timer struct
   realTcount = 0x00;                // Zero superclicks
    TC->CTRLBSET.reg |= TC_CTRLBCLR_CMD_RETRIGGER;   // restart
}

void stopTC3()
{
  TcCount16* TC = (TcCount16*) TC3; // get timer struct
    TC->CTRLBSET.reg |= TC_CTRLBSET_CMD_STOP;   // Stop counter
}


void startTC3()
{
  TcCount16* TC = (TcCount16*) TC3; // get timer struct
    TC->CTRLBSET.reg |= TC_CTRLBSET_CMD_RETRIGGER;   //  Start
} 
