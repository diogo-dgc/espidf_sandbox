#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_log.h"

static const char *TAG = "adc example";

static void task_adc(){
     int x;
    uint16_t adc_data[100];

    while (1) {
        if (ESP_OK == adc_read(&adc_data[0])) {
            ESP_LOGI(TAG, "adc read: %d\r\n", adc_data[0]);
        }

        ESP_LOGI(TAG, "adc read fast:\r\n");

        if (ESP_OK == adc_read_fast(adc_data, 100)) {
            for (x = 0; x < 100; x++) {
                printf("%d\n", adc_data[x]);
            }
        }

        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void app_main()
{
     /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP8266 chip with %d CPU cores, WiFi, ",
            chip_info.cores);

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    vTaskDelay(5000 / portTICK_RATE_MS);

    adc_config_t adc_config;

    // Depend on menuconfig->Component config->PHY->vdd33_const value
    // When measuring system voltage(ADC_READ_VDD_MODE), vdd33_const must be set to 255.
    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.clk_div = 8; // ADC sample collection clock = 80MHz/clk_div = 10MHz
    ESP_ERROR_CHECK(adc_init(&adc_config));

    xTaskCreate(task_adc, "task_adc", 1024, NULL, 5, NULL);

}

