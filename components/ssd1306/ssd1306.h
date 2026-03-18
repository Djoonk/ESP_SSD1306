#pragma once

#include <stdint.h>
#include "driver/i2c_master.h"

/* ------------------------------------------------------------------ */
/*  Display geometry                                                    */
/* ------------------------------------------------------------------ */
#define SSD1306_WIDTH           128
#define SSD1306_HEIGHT           32

/* ------------------------------------------------------------------ */
/*  I2C settings                                                        */
/* ------------------------------------------------------------------ */
#define SSD1306_I2C_ADDR        0x3C    /* 0x3C or 0x3D               */
#define SSD1306_I2C_TIMEOUT_MS  100

/* ------------------------------------------------------------------ */
/*  SSD1306 control bytes                                               */
/* ------------------------------------------------------------------ */
#define SSD1306_CTRL_CMD        0x00
#define SSD1306_CTRL_DATA       0x40

/* ------------------------------------------------------------------ */
/*  SSD1306 command set                                                 */
/* ------------------------------------------------------------------ */
#define SSD1306_SET_CONTRAST            0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME   0xA4
#define SSD1306_NORMAL_DISPLAY          0xA6
#define SSD1306_DISPLAY_OFF             0xAE
#define SSD1306_DISPLAY_ON              0xAF
#define SSD1306_SET_DISPLAY_OFFSET      0xD3
#define SSD1306_SET_COM_PINS            0xDA
#define SSD1306_SET_VCOM_DETECT         0xDB
#define SSD1306_SET_DISPLAY_CLOCK_DIV   0xD5
#define SSD1306_SET_PRECHARGE           0xD9
#define SSD1306_SET_MULTIPLEX           0xA8
#define SSD1306_SET_START_LINE          0x40
#define SSD1306_MEMORY_MODE             0x20
#define SSD1306_COLUMN_ADDR             0x21
#define SSD1306_PAGE_ADDR               0x22
#define SSD1306_COM_SCAN_DEC            0xC8
#define SSD1306_SEG_REMAP_FLIP          0xA1
#define SSD1306_CHARGE_PUMP             0x8D

/* ------------------------------------------------------------------ */
/*  Pixel colors                                                        */
/* ------------------------------------------------------------------ */
#define SSD1306_BLACK   0
#define SSD1306_WHITE   1

/* ------------------------------------------------------------------ */
/*  Public API                                                          */
/* ------------------------------------------------------------------ */

/**
 * @brief Initialize the SSD1306 display.
 *
 * @param dev_handle  I2C device handle, created by the caller via
 *                    i2c_master_bus_add_device().
 */
void ssd1306_init(i2c_master_dev_handle_t dev_handle);

void ssd1306_update(void);
void ssd1306_fill(uint8_t color);
void ssd1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void ssd1306_draw_char(uint8_t x, uint8_t y, const uint8_t *glyph);
void ssd1306_draw_string(uint8_t x, uint8_t y, const char *str);