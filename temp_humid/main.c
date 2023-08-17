#include "../lcd/lcd.h"
#include "../serial/uart_hal.h"
#include "dht11.h"
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t get_hex_ascii(uint8_t d) {
  if (d < 10)
    return '0' + d;
  else
    return 'A' + d - 10;
}

void uart_send_string(char *s) {
  while (*s != 0) {
    uart_send_byte(*s);
    ++s;
  }
}

void uart_send_byte_as_hex(uint8_t d) {
  uint8_t h = (d & 0xf0) >> 4;
  uint8_t l = d & 0x04;

  uart_send_byte(get_hex_ascii(h));
  uart_send_byte(get_hex_ascii(l));
}

void uart_send_byte_as_dec(uint8_t d) {
  uint8_t d2 = (d % 1000) / 100;
  uint8_t d1 = (d % 100) / 10;
  uint8_t d0 = d % 10;

  if (d2 > 0)
    uart_send_byte(get_hex_ascii(d2));
  uart_send_byte(get_hex_ascii(d1));
  uart_send_byte(get_hex_ascii(d0));
}

void lcd_show_byte_as_dec(uint8_t d) {
  uint8_t d2 = (d % 1000) / 100;
  uint8_t d1 = (d % 100) / 10;
  uint8_t d0 = d % 10;

  if (d2 > 0)
    lcd_write_digit(d2);
  lcd_write_digit(d1);
  lcd_write_digit(d0);
}

int main(void) {
  uart_init(9600, 0);
  lcd_init();
  sei();

  uint8_t t_i, t_f, h_i, h_f, cs, csc;

  while (1) {
    _delay_ms(2000);
    start_signal();
    response_signal();

    h_i = read_byte();
    h_f = read_byte();
    t_i = read_byte();
    t_f = read_byte();
    cs = read_byte();
    csc = h_i + h_f + t_i + t_f;

    if (csc - cs == 0) {
      lcd_clear();
      lcd_write_letter(19, 1); // T
      lcd_write_letter(4, 0);  // e
      lcd_write_letter(12, 0); // m
      lcd_write_letter(15, 0); // p
      lcd_write(0x3a);         // :
      lcd_write(0x20);         // space
      lcd_show_byte_as_dec(t_i);
      lcd_write(0x2c); // ,
      lcd_show_byte_as_dec(t_f * 10);
      lcd_write(0xdf);        // °
      lcd_write_letter(2, 1); // C

      lcd_next_line();
      lcd_write_letter(7, 1);  // H
      lcd_write_letter(20, 0); // u
      lcd_write_letter(12, 0); // m
      lcd_write_letter(8, 0);  // i
      lcd_write_letter(3, 0);  // d
      lcd_write(0x3a);         // :
      lcd_write(0x20);         // space
      lcd_show_byte_as_dec(h_i);
      lcd_write(0x2c); // ,
      lcd_show_byte_as_dec(h_f * 10);
      lcd_write(0x25); // %

      uart_send_string("Humidity: ");
      uart_send_byte_as_dec(h_i);
      uart_send_byte(',');
      uart_send_byte_as_dec(h_f * 10);
      uart_send_string("% Temperature: ");
      uart_send_byte_as_dec(t_i);
      uart_send_byte(',');
      uart_send_byte_as_dec(t_f * 10);
      uart_send_string("°C");
    } else
      uart_send_string("Received invalid data");
    uart_send_string("\r\n");
  }

  return 0;
}
