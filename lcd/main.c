#include "lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
  lcd_init();

  _delay_ms(200);

  while (1) {

    lcd_write(7, 1);
    lcd_write(4, 0);
    lcd_write(11, 0);
    lcd_write(11, 0);
    lcd_write(14, 0);

    lcd_next_line();
    lcd_write(22, 1);
    lcd_write(14, 0);
    lcd_write(17, 0);
    lcd_write(11, 0);
    lcd_write(3, 0);

    _delay_ms(2000);
    lcd_clear();

    lcd_write(7, 1);
    lcd_write(0, 0);
    lcd_write(11, 0);
    lcd_write(11, 0);
    lcd_write(14, 0);

    lcd_next_line();
    lcd_write(22, 1);
    lcd_write(4, 0);
    lcd_write(11, 0);
    lcd_write(19, 0);

    _delay_ms(2000);
    lcd_clear();
  }

  return 0;
}
