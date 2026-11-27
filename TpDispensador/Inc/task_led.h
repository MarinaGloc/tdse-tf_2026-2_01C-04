#ifndef INC_TASK_LED_H_
#define INC_TASK_LED_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>

void task_led_init(void);
void task_led_update(void);

uint32_t task_led_get_aciertos(void);
uint32_t task_led_get_errores(void);

#endif
