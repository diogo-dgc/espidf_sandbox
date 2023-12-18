#include "blinkLed.h"

static void ledRoutine(){
    int cnt = 0;
    while (1) {
        ESP_LOGI("LED", "led count: %d\n", cnt++);
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(LED_PINOUT, cnt % 2);
    }
}

void registerLedTask(){
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = LED_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    //start gpio task
    xTaskCreate(ledRoutine, "ledRoutine", 1024, NULL, 10, NULL);

    
}