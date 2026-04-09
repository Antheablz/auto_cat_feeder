#include <stdio.h>
// #include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_flash.h"
#include "esp_system.h"

#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "constants.h"
#include "server.h"


void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    assert(event_base == WIFI_EVENT || event_base == IP_EVENT);
    switch (event_id) {
    case WIFI_EVENT_STA_START:
        {
            ESP_ERROR_CHECK(esp_wifi_connect());
            printf("-----> Wifi Started\n");

            //alternative (and probably correct) way to log
            // ESP_LOGI(TAG, "-----> Starting Wi-Fi");
        }
        break;

    case WIFI_EVENT_STA_CONNECTED:
        {
            wifi_ap_record_t ap_info;
            ESP_ERROR_CHECK(esp_wifi_sta_get_ap_info(&ap_info));
            printf("-----> Connected to Wifi SSID: %s\n", ap_info.ssid);

            // connect_to_mqtt();
        }
        break;

    case WIFI_EVENT_STA_DISCONNECTED:
        {
            printf("-----> Disconnected from Wifi\n");
        }
        break;

    case IP_EVENT_STA_GOT_IP:
        {
            ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
            printf("-----> Device's IP: %d.%d.%d.%d\n", IP2STR(&event->ip_info.ip));
        }
        break;
    }
}

void connect_to_wifi() {
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_USER,
            .password = WIFI_PASS,
            // .threshold.authmode = WIFI_AUTH_OPEN,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void app_main(void) {
    // Setup before we actually do anything
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    connect_to_wifi();
    start_rest_server();
}


