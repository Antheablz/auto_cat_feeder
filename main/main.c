#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"
// #include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"

void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    }
}

void connect_to_wifi(){
    // for grabbing IP info
    // tcpip_adapter_init();

    // ESP_ERROR_CHECK is similar to assert. If arg of ESP_ERR_CHECK != ESP_ok, then err msg is printed and abort() is called
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));

    wifi_config_t wifi_cfg = {
        .sta = {
            .ssid = "***",
            .password = "***"
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf("connected to wifi i think\n");
}


void app_main() {

    connect_to_wifi();

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_NUM_12),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);

    int level;

    while(1) {
        ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_12, 1));
        level = gpio_get_level(GPIO_NUM_12);
        printf("LED ON - level: %d\n", level);

        vTaskDelay(1000 / portTICK_RATE_MS);

        ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_12, 0));
        level = gpio_get_level(GPIO_NUM_12);
        printf("LED OFF - level: %d\n", level);

        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
