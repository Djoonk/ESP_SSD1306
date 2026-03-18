#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ssd1306.h"
#include "i2c.h"

void app_main(void)
{
    i2c_init();
    ssd1306_init();                        /* очищає дисплей всередині */

    ssd1306_draw_string(2, 10, "Hello World");
    ssd1306_update();
}
