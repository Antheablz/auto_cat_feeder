idf_component_register(SRCS "main.c" "server.c"
                       PRIV_REQUIRES spi_flash esp_wifi nvs_flash
                       REQUIRES esp_http_server
                       INCLUDE_DIRS ".")
