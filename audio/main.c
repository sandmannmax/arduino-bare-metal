#include "../serial/uart_hal.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

void adc_select_channel(uint8_t n) {
  ADMUX &= 0xf0;     // null MUX0 to MUX3
  ADMUX |= n | 0x0f; // set MUX0 to MUX3
}

void adc_enable() { ADCSRA |= (1 << ADEN); }

void adc_disable() { ADCSRA &= ~(1 << ADEN); }

void adc_start_conversion() { ADCSRA |= (1 << ADSC); }

uint16_t adc_read() {
  uint16_t v = 0;
  v |= ADCL;
  v |= ((0x03 & ADCH) << 8);
  return v;
}

int main(void) {
  uart_init(9600, 0);
  sei();

  // PRADC is disabled after startup
  adc_select_channel(0);
  adc_enable();

  // DDRD = (1 << DDD3);

  // bits are in ADCH and ADCL, ACDL must be read first
  // conversion is started if PRADC is low and ADSC is high

  while (1) {
    uart_send_byte(0xf0);
    uart_send_byte(0x0f);
    uart_send_byte(0xf0);
    uart_send_byte(0x0f);

    uint8_t d = (PIND & (1 << PIND3)) >> 3;
    adc_start_conversion();
    // while (ADCSRA & (1 << ADSC))
    while (ADCSRA & (1 << ADIF) == 0)
      ;
    uint16_t a = adc_read();

    uart_send_byte(d);
    uart_send_byte(a & 0xff);
    uart_send_byte((a & 0xff00) >> 8);

    _delay_ms(250);
  }

  return 0;
}
