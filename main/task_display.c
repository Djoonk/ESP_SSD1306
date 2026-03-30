#include "shared_state.h"
#include "ssd1306.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

void task_display(void *pvParameters)
{
    ssd1306_init();

    char line[32];

    while (1) {
        float    dist   = 0;
        float    lux    = 0;
        float    temp   = 0;
        float    hum    = 0;
        bool     motion = false;
        bool     sound  = false;
        uint32_t uptime = 0;
        char     status[16] = {0};

        if (STATE_LOCK()) {
            dist   = g_state.distance_cm;
            lux    = g_state.lux;
            temp   = g_state.temperature;
            hum    = g_state.humidity;
            motion = g_state.motion;
            sound  = g_state.sound;
            uptime = g_state.uptime_sec;
            snprintf(status, sizeof(status), "%s", g_state.status);
            STATE_UNLOCK();
        }

        ssd1306_clear();

        snprintf(line, sizeof(line), "D:%5.1fcm L:%4.0flux", dist, lux);
        ssd1306_draw_text(0, 0, line);

        snprintf(line, sizeof(line), "T:%4.1fC   H:%4.1f%%", temp, hum);
        ssd1306_draw_text(0, 1, line);

        snprintf(line, sizeof(line), "PIR:%-3s SND:%-3s",
                 motion ? "YES" : "NO",
                 sound  ? "YES" : "NO");
        ssd1306_draw_text(0, 2, line);

        uint32_t h = uptime / 3600;
        uint32_t m = (uptime % 3600) / 60;
        uint32_t s = uptime % 60;
        snprintf(line, sizeof(line), "UP:%02lu:%02lu:%02lu %.5s",
                 h, m, s, status);
        ssd1306_draw_text(0, 3, line);

        ssd1306_flush();

        vTaskDelay(pdMS_TO_TICKS(200));
    }
    vTaskDelete(NULL);
}