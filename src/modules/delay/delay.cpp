#include "delay.h"
#include <unistd.h>

void delay_us(uint32_t us) { usleep(us); }

void delay_ms(uint32_t ms) { usleep(ms * 1000); }