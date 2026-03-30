#include "i2c_bus.h"
#include "driver/gpio.h"

i2c_master_bus_handle_t g_i2c_bus = NULL;

void i2c_bus_init(void)
{
    if (g_i2c_bus != NULL) return;
    
    i2c_master_bus_config_t cfg = {
        .clk_source               = I2C_CLK_SRC_DEFAULT,
        .i2c_port                 = I2C_NUM_0,
        .scl_io_num               = GPIO_NUM_22,
        .sda_io_num               = GPIO_NUM_21,
        .glitch_ignore_cnt        = 7,
        .flags.enable_internal_pullup = true,
    };
    i2c_new_master_bus(&cfg, &g_i2c_bus);
}