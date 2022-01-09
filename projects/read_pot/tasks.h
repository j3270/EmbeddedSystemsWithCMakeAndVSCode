
#pragma once

#include "task_schedular.h"

uint32_t get_schedular_ticks_from_ms(uint32_t milli_seconds);
uint32_t get_schedular_ticks_from_us(uint32_t micro_seconds);
void init_app();
void toggle_led();
void read_pot();
void set_servo_position();

