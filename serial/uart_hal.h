#include <avr/interrupt.h>
#include <avr/io.h>

#define RX_BUFFER_SIZE 128

void uart_init(uint32_t baud, uint8_t high_speed);
void uart_send_byte(uint8_t c);
uint16_t uart_read_count();
uint8_t uart_read_byte();
