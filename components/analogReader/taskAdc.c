#include "taskAdc.h"

uint16_t adcData[SAMPLE];

void getAdcRead(){
    if (ESP_OK == adc_read(&adcData[FIRST])) {
        ESP_LOGI("ADC", "adc read: %d\r\n", adcData[FIRST]);
    }
}

void getFastAdcRead(){
    ESP_LOGI("ADC", "adc read fast:\r\n");
    if (ESP_OK == adc_read_fast(adcData, SAMPLE)) {
        for (uint8_t i = 0; i < SAMPLE; i++) {
            printf("%d\n", adcData[i]);
        }
    }
}

static void adcRoutine(){
    while (true) {
        getAdcRead();
        //getFastAdcRead();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void registerAdcTask(){
    adc_config_t adc_config;

    // Depend on menuconfig->Component config->PHY->vdd33_const value
    // When measuring system voltage(ADC_READ_VDD_MODE), vdd33_const must be set to 255.
    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.clk_div = 8; // ADC sample collection clock = 80MHz/clk_div = 10MHz
    ESP_ERROR_CHECK(adc_init(&adc_config));
    xTaskCreate(adcRoutine, "adcRoutine", 1024, NULL, 5, NULL);
}