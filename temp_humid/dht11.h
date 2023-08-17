#include <avr/io.h>
#include <util/delay.h>

void start_signal();
void wait_for_high_pulse(uint32_t max_us);
void wait_for_low_pulse(uint32_t max_us);
void response_signal();
uint8_t read_byte();
