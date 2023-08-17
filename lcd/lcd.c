#include "lcd.h"

void toggle_e() {
  PORTB |= (1 << PORTB3);
  _delay_us(1);
  PORTB &= ~(1 << PORTB3);
}

void write_nibble(uint8_t d) {
  PORTD |= (d & 0xf0) | 0x0f;
  toggle_e();
  _delay_us(60);
  PORTD &= 0x0f;
}

void write_byte(uint8_t d) {
  write_nibble(d);
  write_nibble((d & 0x0f) << 4);
}

void write_command(uint8_t d) {
  PORTB &= ~(1 << PORTB4);
  write_byte(d);
}

void lcd_clear() {
  write_command(0x01);
  _delay_ms(100);
}

void lcd_next_line() {
  write_command(0xc0);
  _delay_ms(1);
}

void lcd_write(uint8_t d) {
  PORTB |= (1 << PORTB4);
  write_byte(d);
}

void lcd_write_letter(uint8_t n, uint8_t upper_case) {
  if (upper_case)
    lcd_write(0x41 + n);
  else
    lcd_write(0x61 + n);
}

void lcd_write_digit(uint8_t n) { lcd_write(0x30 + n); }

void lcd_init() {
  DDRB |= (1 << DDB3) | (1 << DDB4);
  DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);
  _delay_ms(100);
  write_nibble(0x30); // wake up
  _delay_ms(30);
  write_nibble(0x30); // wake up
  _delay_ms(10);
  write_nibble(0x30); // wake up
  _delay_ms(10);

  // set 4-bit mode
  write_nibble(0x20);
  // function set DL = 0 (4-bit) N = 1 (2 lines) F = 0 (first font)
  write_byte(0x28);
  // 0x05 = entry mode set
  write_byte(0x0c);
  // 0x05 = entry mode set
  write_byte(0x01);
  // 0x05 = entry mode set
  write_byte(0x05);
}
