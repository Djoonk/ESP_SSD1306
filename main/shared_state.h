#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    float    distance_cm;
    float    lux;
    float    temperature;
    float    humidity;
    bool     motion;
    bool     sound;
    bool     button;
    bool     led_on;
    uint32_t uptime_sec;
    char     status[16];
} SystemState;

extern SystemState        g_state;
extern SemaphoreHandle_t  g_state_mutex;

#define STATE_LOCK()    xSemaphoreTake(g_state_mutex, pdMS_TO_TICKS(10))
#define STATE_UNLOCK()  xSemaphoreGive(g_state_mutex)