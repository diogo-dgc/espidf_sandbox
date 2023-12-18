#ifndef BLINKLED_H
#define BLINKLED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"

#include "esp_log.h"
#include "esp_system.h"

#define LED_PINOUT 16
#define LED_PIN_SEL 1ULL<<LED_PINOUT

static void ledRoutine();
void registerLedTask();

#endif