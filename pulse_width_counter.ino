// Setup TCC0 to capture pulse-width and period Input D12 M0PRO / Serial port / 18_02_2018
volatile boolean periodComplete;
volatile uint16_t isrPeriod;
volatile uint16_t isrPulsewidth;
volatile uint32_t isrCount;
uint16_t period;
uint16_t pulsewidth;
uint32_t count;

void setup()
{
  Serial.begin(115200);                  // Send data back on the Zero's native port


  REG_PM_APBCMASK |= PM_APBCMASK_EVSYS;     // Switch on the event system peripheral
  PM->APBCMASK.reg |= PM_APBCMASK_TCC0;     // ****Enable TCC0 Bus clock (Timer counter control clock)

  REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) |    // Divide the 48MHz system clock by 1 = 48MHz
                    GCLK_GENDIV_ID(5);      // Set division on Generic Clock Generator (GCLK) 5
  while (GCLK->STATUS.bit.SYNCBUSY);        // Wait for synchronization

  REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                     GCLK_GENCTRL_GENEN |         // Enable GCLK 5
                     GCLK_GENCTRL_SRC_DFLL48M |   // Set the clock source to 48MHz
                     GCLK_GENCTRL_ID(5);          // Set clock source on GCLK 5
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization*/

  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // ***Enable the generic clock...
                     GCLK_CLKCTRL_GEN_GCLK5 |     // ***.... on GCLK5...
                     GCLK_CLKCTRL_ID_EIC;         // ***... to feed the GCLK5 to EIC peripheral
  while (GCLK->STATUS.bit.SYNCBUSY);              // ***Wait for synchronization

  REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable the generic clock...
                     GCLK_CLKCTRL_GEN_GCLK5 |     // ....on GCLK5
                     GCLK_CLKCTRL_ID_TCC0_TCC1;   // Feed the GCLK5 to TCC0 and TCC1
  while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

  //REG_EIC_EVCTRL |= EIC_EVCTRL_EXTINTEO3;                      // Enable event output on external interrupt 3
  // attachInterrupt(12, NULL, HIGH);                            // Attach interrupts to digital pin 12 (external interrupt 3)
  //PORT->Group[PORTA].DIRCLR.reg = PORT_DIRCLR_DIRCLR(1<<19);   // ***Set pin PA19 pin as input
  PORT->Group[PORTA].PMUX[19 >> 1].reg |= PORT_PMUX_PMUXO_A;     // ***Connect PA19 pin to peripheral A (EXTINT[3])
  PORT->Group[PORTA].PINCFG[19].reg |= PORT_PINCFG_PMUXEN;       // ***Enable pin peripheral multiplexation


  /* - Configuración del EIC - */

  REG_EIC_EVCTRL |= EIC_EVCTRL_EXTINTEO3;         // ***Enable event from pin on external interrupt 3 (EXTINT03)
  REG_EIC_CONFIG0 |= EIC_CONFIG_SENSE3_HIGH;      // ***Set event on HIGH edge of signal
  REG_EIC_CTRL |= EIC_CTRL_ENABLE;                // ***Enable EIC peripheral
  while (EIC->STATUS.bit.SYNCBUSY);               // ***Wait for synchronization

  REG_EVSYS_USER = EVSYS_USER_CHANNEL(1) |                                // Attach the event user (receiver) to channel 0 (n + 1)
                   EVSYS_USER_USER(EVSYS_ID_USER_TCC0_EV_1);              // Set the event user (receiver) as timer TCC0, event 1

  REG_EVSYS_CHANNEL = EVSYS_CHANNEL_EDGSEL_NO_EVT_OUTPUT |                // No event edge detection
                      EVSYS_CHANNEL_PATH_ASYNCHRONOUS |                   // Set event path as asynchronous
                      EVSYS_CHANNEL_EVGEN(EVSYS_ID_GEN_EIC_EXTINT_3) |    // Set event generator (sender) as external interrupt 3
                      EVSYS_CHANNEL_CHANNEL(0);                           // Attach the generator (sender) to channel 0

  REG_TCC0_EVCTRL |= TCC_EVCTRL_MCEI1 |           // Enable the match or capture channel 1 event input
                     TCC_EVCTRL_MCEI0 |           //.Enable the match or capture channel 0 event input
                     TCC_EVCTRL_TCEI1 |           // Enable the TCC event 1 input
                     /*TCC_EVCTRL_TCINV1 |*/      // Invert the event 1 input
                     TCC_EVCTRL_EVACT1_PPW;       // Set up the timer for capture: CC0 period, CC1 pulsewidth

  //NVIC_DisableIRQ(TCC0_IRQn);
  //NVIC_ClearPendingIRQ(TCC0_IRQn);
  NVIC_SetPriority(TCC0_IRQn, 0);      // Set the Nested Vector Interrupt Controller (NVIC) priority for TCC0 to 0 (highest)
  NVIC_EnableIRQ(TCC0_IRQn);           // Connect the TCC0 timer to the Nested Vector Interrupt Controller (NVIC)

  REG_TCC0_INTENSET = TCC_INTENSET_MC1 |            // Enable compare channel 1 (CC1) interrupts
                      TCC_INTENSET_MC0;             // Enable compare channel 0 (CC0) interrupts

  REG_TCC0_CTRLA |= TCC_CTRLA_CPTEN1 |              // Enable capture on CC1
                    TCC_CTRLA_CPTEN0 |              // Enable capture on CC0
                    TCC_CTRLA_PRESCALER_DIV1 |     // Set prescaler to 1, 48MHz/1 = 48MHz
                    TCC_CTRLA_ENABLE;               // Enable TCC0
  while (TCC0->SYNCBUSY.bit.ENABLE);                // Wait for synchronization
}

void loop()
{
  if (periodComplete)                             // Check if the period is complete
  {
    noInterrupts();                               // Read the new period and pulse-width
    period = isrPeriod;
    pulsewidth = isrPulsewidth;
    count = isrCount;
    interrupts();
    Serial.print(period);                      // Output the results
    Serial.print(F("   "));
    Serial.print(pulsewidth);
    Serial.print(F("   "));
    Serial.println(count);
    periodComplete = false;                       // Start a new period
  }
}

void TCC0_Handler()                              // Interrupt Service Routine (ISR) for timer TCC0
{
  // Check for match counter 0 (MC0) interrupt
  if (TCC0->INTFLAG.bit.MC0)
  {
    isrPeriod = REG_TCC0_CC0;                   // Copy the period
    periodComplete = true;                       // Indicate that the period is complete
  }

  // Check for match counter 1 (MC1) interrupt
  if (TCC0->INTFLAG.bit.MC1)
  {
    isrPulsewidth = REG_TCC0_CC1;               // Copy the pulse-width
    isrCount++;
  }
}
