#include "adc_hal.h"

static volatile uint8_t adc_running = 0;

void adc_init() {
  ADMUX |= (1 << REFS0) | (0b0101 << MUX0); // set MUX0 and MUX2
  ADCSRA |= (1 << ADEN) | (1 << ADIE) | (0b111 << ADPS0);
  DIDR0 |= 1 << ADC5D; // disable digital input buffer
  adc_start_conversion();
}

void adc_start_conversion() {
  adc_running = 1;
  ADCSRA |= (1 << ADSC);
}

uint16_t adc_read() {
  uint8_t adch = 0;
  uint8_t adcl = 0;
  adc_start_conversion();
  while (adc_running > 0)
    ;
  adcl = ADCL;
  adch = ADCH;
  return (adch << 8) | adcl;
}

ISR(ADC_vect) { adc_running = 0; }
