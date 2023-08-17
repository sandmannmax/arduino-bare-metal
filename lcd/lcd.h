#include <avr/io.h>
#include <util/delay.h>

void lcd_init();
void lcd_clear();
void lcd_next_line();
void lcd_write(uint8_t d);
void lcd_write_letter(uint8_t n, uint8_t upper_case);
void lcd_write_digit(uint8_t n);
