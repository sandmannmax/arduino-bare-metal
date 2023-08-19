#include <avr/interrupt.h>
#include <avr/io.h>

void adc_init();
void adc_start_conversion();
uint16_t adc_read();
