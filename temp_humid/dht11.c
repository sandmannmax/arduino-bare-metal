#include "dht11.h"

void start_signal() {
  DDRD |= (1 << DDD2);
  PORTD &= ~(1 << PORTD2);
  _delay_ms(20);
  PORTD |= (1 << PORTD2);
}

void wait_for_high_pulse(uint32_t max_us) {
  uint32_t max_cycles = max_us * (F_CPU / 1000000);
  uint32_t cycles = 0;
  while ((PIND & (1 << PIND2)) == 0 &&
         cycles < max_cycles) // wait for high pulse
    ++cycles;
}

void wait_for_low_pulse(uint32_t max_us) {
  uint32_t max_cycles = max_us * (F_CPU / 1000000);
  uint32_t cycles = 0;
  while (PIND & (1 << PIND2) && cycles < max_cycles) // wait for low pulse
    ++cycles;
}

void response_signal() {
  DDRD &= ~(1 << DDD2);
  wait_for_low_pulse(50);
  wait_for_high_pulse(100);
  wait_for_low_pulse(100);
}

uint8_t read_byte() {
  uint8_t d = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    wait_for_high_pulse(60);
    _delay_us(50);
    if (PIND & (1 << PIND2))
      d = (d << 1) | 0x01;
    else
      d = d << 1;
    wait_for_low_pulse(80);
  }

  return d;
}
