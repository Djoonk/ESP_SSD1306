#include "dht11.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "rom/ets_sys.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DHT11_PIN GPIO_NUM_4

dht11_data_t dht11_read(void)
{
    dht11_data_t result = {0, 0, false};
    uint8_t data[5] = {0};

    gpio_set_direction(DHT11_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(DHT11_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(20));
    gpio_set_level(DHT11_PIN, 1);
    ets_delay_us(30);

    gpio_set_direction(DHT11_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(DHT11_PIN, GPIO_PULLUP_ONLY);

    int64_t t = esp_timer_get_time();
    while (gpio_get_level(DHT11_PIN) == 1)
        if (esp_timer_get_time() - t > 100) return result;

    t = esp_timer_get_time();
    while (gpio_get_level(DHT11_PIN) == 0)
        if (esp_timer_get_time() - t > 100) return result;

    t = esp_timer_get_time();
    while (gpio_get_level(DHT11_PIN) == 1)
        if (esp_timer_get_time() - t > 100) return result;

    for (int i = 0; i < 40; i++) {
        t = esp_timer_get_time();
        while (gpio_get_level(DHT11_PIN) == 0)
            if (esp_timer_get_time() - t > 100) return result;

        ets_delay_us(40);
        int bit = gpio_get_level(DHT11_PIN);
        data[i / 8] <<= 1;
        if (bit) data[i / 8] |= 1;

        t = esp_timer_get_time();
        while (gpio_get_level(DHT11_PIN) == 1)
            if (esp_timer_get_time() - t > 100) return result;
    }

    if (data[4] != (uint8_t)(data[0] + data[1] + data[2] + data[3]))
        return result;

    result.humidity    = data[0];
    result.temperature = data[2];
    result.valid       = true;
    return result;
}