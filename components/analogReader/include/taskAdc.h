#ifndef TASKADC_H
#define TASKADC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/adc.h"
#include "esp_log.h"

#define SAMPLE 100
#define FIRST 0

void getAdcRead();
void getFastAdcRead();
void registerAdcTask();
static void adcRoutine();

#endif