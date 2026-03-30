#include "shared_state.h"
#include "i2c_bus.h"
#include "dht11.h"
#include "ssd1306.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "task_sensors.h"

#define TRIG_PIN  GPIO_NUM_5
#define ECHO_PIN  GPIO_NUM_19
#define PIR_PIN   GPIO_NUM_13
#define SOUND_PIN GPIO_NUM_34
#define BTN_PIN   GPIO_NUM_18


i2c_master_dev_handle_t bh1750_dev = NULL;
static const char *TAG = "SENSORS";

void bh1750_init(void)
{
    i2c_device_config_t cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = 0x23,
        .scl_speed_hz    = 100000,
    };
    i2c_master_bus_add_device(g_i2c_bus, &cfg, &bh1750_dev);
}

static float bh1750_read(void)
{
    uint8_t cmd  = 0x10;
    uint8_t raw[2] = {0};

    if (i2c_master_transmit(bh1750_dev, &cmd, 1, 50) != ESP_OK)
        return 0;

    vTaskDelay(pdMS_TO_TICKS(180));

    if (i2c_master_receive(bh1750_dev, raw, 2, 50) != ESP_OK)
        return 0;

    return ((raw[0] << 8) | raw[1]) / 1.2f;
}

static float measure_distance(void)
{
    gpio_set_level(TRIG_PIN, 0); esp_rom_delay_us(2);
    gpio_set_level(TRIG_PIN, 1); esp_rom_delay_us(10);
    gpio_set_level(TRIG_PIN, 0);

    int64_t t = esp_timer_get_time();
    while (!gpio_get_level(ECHO_PIN))
        if (esp_timer_get_time() - t > 25000) return -1;

    int64_t s = esp_timer_get_time();
    while (gpio_get_level(ECHO_PIN))
        if (esp_timer_get_time() - s > 25000) return -1;

    return (esp_timer_get_time() - s) * 0.034f / 2.0f;
}

void task_sensors(void *pvParameters)
{
    
    gpio_set_direction(TRIG_PIN,  GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_PIN,  GPIO_MODE_INPUT);
    gpio_set_direction(PIR_PIN,   GPIO_MODE_INPUT);
    gpio_set_direction(SOUND_PIN, GPIO_MODE_INPUT);
    gpio_set_direction(BTN_PIN,   GPIO_MODE_INPUT);
    gpio_set_pull_mode(BTN_PIN,   GPIO_PULLUP_ONLY);

    while (1) {
        float        dist  = measure_distance();
        float        lux   = bh1750_read();
        dht11_data_t dht   = dht11_read();
        int          motion = gpio_get_level(PIR_PIN);
        int          sound  = gpio_get_level(SOUND_PIN);
        int          btn    = !gpio_get_level(BTN_PIN);

        ESP_LOGI(TAG, "D:%.1f L:%.1f T:%.1f H:%.1f PIR:%d SND:%d BTN:%d",
                 dist, lux, dht.temperature, dht.humidity,
                 motion, sound, btn);

        if (STATE_LOCK()) {
            if (dist > 0 && dist < 400) g_state.distance_cm  = dist;
            if (lux  > 0)               g_state.lux           = lux;
            if (dht.valid) {
                g_state.temperature = dht.temperature;
                g_state.humidity    = dht.humidity;
            }
            g_state.motion = motion;
            g_state.sound  = sound;
            g_state.button = btn;
            STATE_UNLOCK();
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}