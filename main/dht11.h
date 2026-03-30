#pragma once
#include <stdbool.h>

typedef struct {
    float temperature;
    float humidity;
    bool  valid;
} dht11_data_t;

dht11_data_t dht11_read(void);