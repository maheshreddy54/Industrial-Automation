#include "DueTimer.h"

int count_q = 0;      // quadrature decoder hardware counts

void setup() {

  Serial.begin(9600); //115200 or 9600
  analogWriteResolution(12);    // set DAC output to maximum 12-bits
  Timer3.attachInterrupt(update).start(100000); // start ISR timer3 (not used by quad decoder and PWM) at 1 ms, which is 1kHz
  
  // setup for encoder position measurement (Digital pins 2 and 13)
  // This is described in Chapter 36 of the SAM3X8E datasheet
  
    REG_PMC_PCER0 = PMC_PCER0_PID27;   
    REG_TC0_CMR0 = TC_CMR_TCCLKS_XC0;  

    REG_TC0_BMR = TC_BMR_QDEN
                | TC_BMR_POSEN 
                | TC_BMR_EDGPHA; 

    REG_TC0_CCR0 = TC_CCR_CLKEN 
                 | TC_CCR_SWTRG;

    pinMode(10, OUTPUT);
    pinMode(8, OUTPUT);

}

void loop() {
  //count_q = REG_TC0_CV0; 
  //Serial.println(count_q);
  
  analogWrite(10, 255);

}

void update() {
  count_q = REG_TC0_CV0; 
  Serial.println(count_q);

}
