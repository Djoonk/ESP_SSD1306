#pragma once
#include <stdint.h>

#define SSD1306_ADDR   0x3C
#define SSD1306_WIDTH  128
#define SSD1306_HEIGHT 32

void ssd1306_init(void);
void ssd1306_clear(void);
void ssd1306_draw_text(uint8_t col, uint8_t row, const char *text);
void ssd1306_flush(void);