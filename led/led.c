#include <avr/io.h>
#include <util/delay.h>

int main(void) {
  DDRB |= (1 << DDB5);
  DDRB |= (1 << DDB4);

  while (1) {
    PORTB |= (1 << PORTB5);
    PORTB |= (1 << PORTB4);
    _delay_ms(10);
    PORTB &= ~(1 << PORTB5);
    _delay_ms(490);
    PORTB &= ~(1 << PORTB4);
    _delay_ms(500);
  }

  return 0;
}
