  REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | 0x1B) ;
  while (GCLK->STATUS.bit.SYNCBUSY == 1); // wait for sync

  // The type cast must fit with the selected timer mode
  TcCount16* TC = (TcCount16*) TC3; // get timer struct

  TC->CTRLA.reg &= ~TC_CTRLA_ENABLE;   // Disable TC (to enable configuration mode)
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;  // Set Timer counter Mode to 16 bits
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  TC->CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ; // Set TC as  Match Frq
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV256;   // Set prescaler
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
  TC->CC[0].reg = 18743; // 18743 OK
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

  TC->INTENSET.reg = 0;              // disable all interrupts
  TC->INTENSET.bit.MC0 = 1;          // enable compare match to CC0

  // Enable InterruptVector
  NVIC_EnableIRQ(TC3_IRQn); // interrupt > TC3_Handler(){}

  TC->CTRLA.reg |= TC_CTRLA_ENABLE; // Enable TC (configuration mode finished)
  while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
