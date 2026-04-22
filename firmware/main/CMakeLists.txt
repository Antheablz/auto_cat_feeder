idf_component_register(SRCS "main.c" "server.c"
                       PRIV_REQUIRES spi_flash esp_wifi nvs_flash esp_http_server esp_driver_gpio
                       INCLUDE_DIRS ".")

littlefs_create_partition_image(storage ../frontend FLASH_IN_PROJECT)
