#include "driver/i2c_master.h"
#include "ssd1306.h"

/* ---- Adjust pins to your board ---- */
#define I2C_SCL_PIN     22
#define I2C_SDA_PIN     21
#define I2C_BUS_SPEED   400000   /* 400 kHz */

void app_main(void)
{
    /* 1. Create I2C bus */
    i2c_master_bus_config_t bus_cfg = {
        .i2c_port            = I2C_NUM_0,
        .sda_io_num          = I2C_SDA_PIN,
        .scl_io_num          = I2C_SCL_PIN,
        .clk_source          = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt   = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_cfg, &bus));

    /* 2. Add SSD1306 device to the bus */
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address  = SSD1306_I2C_ADDR,
        .scl_speed_hz    = I2C_BUS_SPEED,
    };
    i2c_master_dev_handle_t ssd1306_dev;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &dev_cfg, &ssd1306_dev));

    /* 3. Initialize the display — pass handle once, library stores it */
    ssd1306_init(ssd1306_dev);

    /* 4. Draw something */
    ssd1306_fill(SSD1306_BLACK);
    ssd1306_draw_string(0, 0, "Hello ESP32!");
    ssd1306_update();
}
