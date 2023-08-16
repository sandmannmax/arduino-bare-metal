#include <avr/io.h>
#include <util/delay.h>

void lcd_init();
void lcd_clear();
void lcd_next_line();
void lcd_write(uint8_t n, uint8_t upper_case);
