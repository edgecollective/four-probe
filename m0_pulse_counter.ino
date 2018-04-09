#define PinLED  13

volatile boolean Pp = true;

volatile unsigned long PulseCnt, tcc0_cnt, Period, PWidth;


void setup() {
  // put your setup code here, to run once:
  
  SerialUSB.begin(19200);                   // Send data back on the Zero's native port
  while(!SerialUSB);                        // Wait for the SerialUSB port to be ready

  pinMode(PinLED, OUTPUT);
  digitalWrite(PinLED, LOW);
  
 
  REG_PM_APBCMASK |=  PM_APBCMASK_EVSYS;    // Switch on the event system peripheral
  PM->APBCMASK.reg |= PM_APBCMASK_TCC0;     // Enable TCC0 Bus clock (Timer counter control clock)

 /*
  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |          // Divide the 48MHz system clock by 3 = 16MHz
                    GCLK_GENDIV_ID(2);            // Set division on Generic Clock Generator (GCLK) 2
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  REG_GCLK_GENCTRL = //GCLK_GENCTRL_IDC |         // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |         // Enable GCLK 2
                     GCLK_GENCTRL_SRC_DFLL48M |   // Set the clock source to 48MHz
                     GCLK_GENCTRL_ID(2);          // Set clock source on GCLK 2
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization
*/

  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable the generic clock...
                     GCLK_CLKCTRL_GEN_GCLK0 |     // .... on GCLK0...
                     GCLK_CLKCTRL_ID_EIC;         // ... to feed the GCLK0 to EIC peripheral
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization
  SerialUSB.println("Configuración GCLK_CLKCTRL realizada para EIC");
  
  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable the generic clock...
                     GCLK_CLKCTRL_GEN_GCLK0 |     // ....on GCLK0...
                     GCLK_CLKCTRL_ID_TCC0_TCC1;   // ... to feed the GCLK5 to TCC0 and TCC1 peripheral
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization
  SerialUSB.println("Configuración GCLK_CLKCTRL realizada para TCC0/TCC1");


  //PORT->Group[PORTA].DIRCLR.reg = PORT_DIRCLR_DIRCLR(1<<19);   // Set pin PA19 pin as input
  PORT->Group[PORTA].PMUX[19 >> 1].reg |= PORT_PMUX_PMUXO_A;     // Connect PA19 pin to peripheral A (EXTINT[3]) 
  PORT->Group[PORTA].PINCFG[19].reg |= PORT_PINCFG_PMUXEN;       // Enable pin peripheral multiplexation 
  //PORT->Group[PORTA].PINCFG[19].bit.INEN = PORT_PINCFG_INEM;   // Enable input pin buffer
  //attachInterrupt(12, NULL, RISING);                           // Attach external interrupt to digital pin 12 (external interrupt 3)
  SerialUSB.println("Configuración PA19/EXTINT_03 -Pin 12- realizada");


  /* - Configuración del EIC - */
  
  REG_EIC_EVCTRL |= EIC_EVCTRL_EXTINTEO3;         // Enable event from pin on external interrupt 3 (EXTINT03)
  REG_EIC_CONFIG0 |= EIC_CONFIG_SENSE3_RISE;      // Set event on rising edge of signal
  REG_EIC_CTRL |= EIC_CTRL_ENABLE;                // Enable EIC peripheral
  while (EIC->STATUS.bit.SYNCBUSY);               // Wait for synchronization

  //REG_EIC_INTENSET = EIC_INTENSET_EXTINT3;      // External interrupt is enable
  

  /* - Configuración del EVSYS - */
 
  REG_EVSYS_USER = EVSYS_USER_CHANNEL(1) |                                // Attach the event user (receiver) to channel n=0 (n + 1)
                   EVSYS_USER_USER(EVSYS_ID_USER_TCC0_EV_0);              // Set the event user (receiver) as timer TCC0, event 1
  SerialUSB.println("Configuración EVE_SYS_USER realizada");

  REG_EVSYS_CHANNEL = EVSYS_CHANNEL_EDGSEL_NO_EVT_OUTPUT |                // No event output edge detection
                      EVSYS_CHANNEL_PATH_ASYNCHRONOUS |                   // Set event path as asynchronous
                      EVSYS_CHANNEL_EVGEN(EVSYS_ID_GEN_EIC_EXTINT_3) |    // Set event generator (sender) as external interrupt 3
                      EVSYS_CHANNEL_CHANNEL(0);                           // Attach the generator (sender) to channel 0
  SerialUSB.println("Configuración EVE_SYS_CHANNEL realizada");


  /* - Configuración de TCC0 - */

  REG_TCC0_CTRLA &=~TCC_CTRLA_ENABLE;             // Disable TCC0 peripheral
  //while (TCC0->SYNCBUSY.bit.ENABLE);            // Wait for synchronization
  SerialUSB.println("Comenzando configuración de TCC0");

  REG_TCC0_CTRLBCLR |= TCC_CTRLBCLR_DIR;          // Clear DIR bit to count up
  while (TCC0->SYNCBUSY.bit.CTRLB);               // Wait for (write) synchronization
  SerialUSB.println("Configuración TCC0 CTRLB realizada");

  REG_TCC0_EVCTRL |= TCC_EVCTRL_TCEI0 |           // Enable the TCC event 0 input
                     //TCC_EVCTRL_TCEI1 |         // Enable the TCC event 1 input
                     //TCC_EVCTRL_TCINV1 |        // Invert the event 1 input
                     TCC_EVCTRL_EVACT0_COUNT;     // Set up TCC timer/counter to count on event
  SerialUSB.println("Configuración TCC0_EVCTRL realizada");
  
  REG_TCC0_CTRLA |= //TCC_CTRLA_CPTEN0 |          // Enable capture on CC0
                    //TCC_CTRLA_PRESCALER_DIV16 | // Set prescaler to 16, 16MHz/16 = 1MHz
                    TCC_CTRLA_ENABLE;             // Enable TCC0
  while (TCC0->SYNCBUSY.bit.ENABLE);              // Wait for synchronization
  SerialUSB.println("Módulo TCC0 habilitado");

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(1000);  // Wait one second
  
  digitalWrite(PinLED, Pp);
  Pp = !Pp;

  REG_TCC0_CTRLBSET = TCC_CTRLBSET_CMD_READSYNC;  // Trigger a read synchronization on the COUNT register
  while (TCC0->SYNCBUSY.bit.CTRLB);               // Wait for the CTRLB register write synchronization
  while (TCC0->SYNCBUSY.bit.COUNT);               // Wait for the COUNT register read sychronization
  SerialUSB.print("TCC0 count: ");
  //SerialUSB.println(tcc0_cnt, DEC);             // Print the result
  SerialUSB.println(REG_TCC0_COUNT, DEC);         // Print the result

}


/*
void EIC_Handler()                            // Interrupt Service Routine (ISR) for External Interrupt Controller (EIC)
{
  if(EIC->INTFLAG.bit.EXTINT3)
    EIC->INTFLAG.reg = EIC_INTFLAG_EXTINT3;   // Clear interrupt flag by writing '1' on it
}
*/
