#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "shared_state.h"
#include "i2c_bus.h"
#include <string.h>
#include "ssd1306.h"
#include "task_sensors.h"

SystemState       g_state       = {0};
SemaphoreHandle_t g_state_mutex = NULL;

void task_sensors(void *p);
void task_display(void *p);
void task_system(void *p);

void app_main(void)
{
    i2c_bus_init();
    bh1750_init();
    ssd1306_init();

    g_state_mutex = xSemaphoreCreateMutex();
    strncpy(g_state.status, "INIT", sizeof(g_state.status) - 1);

    xTaskCreate(task_sensors, "sensors", 4096, NULL, 3, NULL);
    xTaskCreate(task_display, "display", 4096, NULL, 2, NULL);
    xTaskCreate(task_system,  "system",  2048, NULL, 1, NULL);
}