#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stddef.h>

/* Display dimensions */
#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT  32

/* I2C address */
#define SSD1306_ADDR    0x3C

/* Control bytes */
#define SSD1306_CTRL_CMD    0x00   /* next byte(s) are commands */
#define SSD1306_CTRL_DATA   0x40   /* next byte(s) are data     */

/* SSD1306 commands */
#define SSD1306_SET_CONTRAST            0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME   0xA4
#define SSD1306_NORMAL_DISPLAY          0xA6
#define SSD1306_INVERT_DISPLAY          0xA7
#define SSD1306_DISPLAY_OFF             0xAE
#define SSD1306_DISPLAY_ON              0xAF
#define SSD1306_SET_DISPLAY_OFFSET      0xD3
#define SSD1306_SET_COM_PINS            0xDA
#define SSD1306_SET_VCOM_DETECT         0xDB
#define SSD1306_SET_DISPLAY_CLOCK_DIV   0xD5
#define SSD1306_SET_PRECHARGE           0xD9
#define SSD1306_SET_MULTIPLEX           0xA8
#define SSD1306_SET_LOW_COLUMN          0x00
#define SSD1306_SET_HIGH_COLUMN         0x10
#define SSD1306_SET_START_LINE          0x40
#define SSD1306_MEMORY_MODE             0x20
#define SSD1306_COLUMN_ADDR             0x21
#define SSD1306_PAGE_ADDR               0x22
#define SSD1306_COM_SCAN_INC            0xC0
#define SSD1306_COM_SCAN_DEC            0xC8
#define SSD1306_SEG_REMAP_NORMAL        0xA0
#define SSD1306_SEG_REMAP_FLIP          0xA1
#define SSD1306_CHARGE_PUMP             0x8D

/* Pixel color */
#define SSD1306_WHITE   1
#define SSD1306_BLACK   0

/* Frame buffer: 128 * 32 / 8 = 512 bytes */
extern uint8_t buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];

/* ------------------------------------------------------------------ */
/*  Public API                                                          */
/* ------------------------------------------------------------------ */

/**
 * @brief  Initialise SSD1306. Call i2c_init() before this.
 */
void ssd1306_init(void);

/**
 * @brief  Send frame buffer to the display.
 */
void ssd1306_update(void);

/**
 * @brief  Fill entire frame buffer with 0x00 (black) or 0xFF (white).
 * @param  color  SSD1306_BLACK or SSD1306_WHITE
 */
void ssd1306_fill(uint8_t color);

/**
 * @brief  Set or clear a single pixel.
 * @param  x, y   Pixel coordinates (0-based)
 * @param  color  SSD1306_WHITE or SSD1306_BLACK
 */
void ssd1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color);

/**
 * @brief  Draw a 5-column glyph (font data: 5 bytes, each byte = 1 column, bit0 = top).
 * @param  x, y   Top-left corner of the character
 * @param  glyph  Pointer to 5-byte font array
 */
void ssd1306_draw_char(uint8_t x, uint8_t y, const uint8_t *glyph);

/**
 * @brief  Draw a null-terminated string using the built-in 5x7 ASCII font.
 *         Characters outside the built-in set are rendered as a blank glyph.
 * @param  x, y  Top-left corner of the first character
 * @param  str   Null-terminated string
 */
void ssd1306_draw_string(uint8_t x, uint8_t y, const char *str);

#endif /* SSD1306_H */
