#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include <stddef.h>
#include "i2c.h"
#include "esp_err.h"

/* I2C configuration */
#define I2C_PORT        I2C_NUM_0
#define I2C_SDA_PIN     21
#define I2C_SCL_PIN     22
#define I2C_FREQ_HZ     400000

/* Functions */
void i2c_init(void);

esp_err_t i2c_write(uint8_t dev_addr, const uint8_t *data, size_t len);
esp_err_t i2c_read(uint8_t dev_addr, uint8_t *data, size_t len);

#endif