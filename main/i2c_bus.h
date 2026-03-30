#pragma once
#include "driver/i2c_master.h"

extern i2c_master_bus_handle_t g_i2c_bus;

void i2c_bus_init(void);