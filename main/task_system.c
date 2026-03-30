#include "shared_state.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <string.h>

#define LED_PIN  GPIO_NUM_2
#define BTN_PIN  GPIO_NUM_18

static const char *TAG = "SYS";

void task_system(void *pvParameters)
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 0);

    int      btn_last  = 1;
    bool     led_state = false;
    int      stats_tick = 0;

    while (1) {
        int btn = gpio_get_level(BTN_PIN);

        if (STATE_LOCK()) {
            g_state.uptime_sec++;

            // Health check
            bool ok = (g_state.distance_cm > 0 &&
                       g_state.temperature > 0 &&
                       g_state.lux >= 0);
            strncpy(g_state.status,
                    ok ? "OK" : "SENSOR ERR",
                    sizeof(g_state.status) - 1);

            // Кнопка → toggle LED
            if (btn == 0 && btn_last == 1) {
                led_state = !led_state;
                gpio_set_level(LED_PIN, led_state);
                g_state.led_on = led_state;
                ESP_LOGI(TAG, "BTN → LED: %s", led_state ? "ON" : "OFF");
            }

            g_state.button = (btn == 0);
            STATE_UNLOCK();
        }

        btn_last = btn;

        // Статистика задач кожні 30 сек
        // if (++stats_tick >= 30) {
        //     stats_tick = 0;
        //     char stats[512];
        //     vTaskList(stats);
        //     ESP_LOGI(TAG, "\nTask        State Prio Stack Num\n%s", stats);
        // }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}