#include <avr/io.h>

void ledInit(void) { DDRB |= (1 << DDB5); }

void ledToggle(void) {
  unsigned char v = PORTB & (1 << PORTB5);
  PORTB = ~v;
}
