idf_component_register(
    SRCS
        "main.c"
        "i2c_bus.c"
        "ssd1306.c"
        "dht11.c"
        "task_sensors.c"
        "task_display.c"
        "task_system.c"
    INCLUDE_DIRS "."
    REQUIRES
        esp_driver_i2c
        esp_driver_gpio
        freertos
        esp_timer
        log
)