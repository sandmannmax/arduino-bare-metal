#include "lcd.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void) {
  lcd_init();

  _delay_ms(200);

  while (1) {

    lcd_write_letter(7, 1);
    lcd_write_letter(4, 0);
    lcd_write_letter(11, 0);
    lcd_write_letter(11, 0);
    lcd_write_letter(14, 0);

    lcd_next_line();
    lcd_write_letter(22, 1);
    lcd_write_letter(14, 0);
    lcd_write_letter(17, 0);
    lcd_write_letter(11, 0);
    lcd_write_letter(3, 0);

    _delay_ms(2000);
    lcd_clear();

    lcd_write_letter(7, 1);
    lcd_write_letter(0, 0);
    lcd_write_letter(11, 0);
    lcd_write_letter(11, 0);
    lcd_write_letter(14, 0);

    lcd_next_line();
    lcd_write_letter(22, 1);
    lcd_write_letter(4, 0);
    lcd_write_letter(11, 0);
    lcd_write_letter(19, 0);

    _delay_ms(2000);
    lcd_clear();
  }

  return 0;
}
