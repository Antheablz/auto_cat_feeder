#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"

#include "esp_netif.h"
#include "mqtt_client.h"

// #include "mqtt.h"

#include "constants.h"

// static const char* TAG = "MAIN";

void mqtt_event_handler(void *handler_args, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    switch (event_id) {
    case MQTT_EVENT_BEFORE_CONNECT :
        {
            printf("-----> BEFORE MQTT CONNECTION\n");
        }
        break;

    case MQTT_EVENT_CONNECTED:
        {
            printf("-----> Connected to MQTT\n");
        }
        break;

    case MQTT_EVENT_ERROR:
        {
            esp_mqtt_event_t *err = (esp_mqtt_event_t*) event_data;
            
            printf("-----> MQTT ERROR: %d\n", err->error_handle->error_type);  //MQTT_ERROR_TYPE_ESP_TLS
        }
        break;

    case MQTT_EVENT_DISCONNECTED:
        {
            printf("-----> MQTT DISCONNECT\n");
        }
        break;
    }



}

void connect_to_mqtt() {

    esp_mqtt_client_config_t mqtt_cfg = {
        // .protocol_ver = MQTT_PROTOCOL_V_3_1_1,
        // .uri = "mqtt://10.0.0.177:1883",
        // .host = "10.0.0.177",
        // .port = 1883
        // .uri = "mqtt://test.mosquitto.org:1883/",
        
        // .host = "192.168.0.227",
        // .port = 1883,
        .transport = MQTT_TRANSPORT_OVER_TCP,
        .uri = "mqtt://192.168.0.227:1883",
        .username = "anthea",
        .password = "stocking-inventor-frost",
    };


    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    if (client == NULL) {
        printf("THIS IS NOT WORKING\n");
    }
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
    // ESP_ERROR_CHECK(esp_mqtt_client_start(client));
}

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

            connect_to_mqtt();
        }
        break;

    case SYSTEM_EVENT_STA_DISCONNECTED:
        {
            printf("-----> Disconnected from Wifi\n");
        }
        break;

    case IP_EVENT_STA_GOT_IP:
        {
            tcpip_adapter_ip_info_t ip_info;
            ESP_ERROR_CHECK(tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ip_info));
            printf("-----> Device's IP: %s\n", ip4addr_ntoa(&ip_info.ip));
        }
        break;
    }


}

void connect_to_wifi(){

    // // for grabbing IP info of the esp chip
    // tcpip_adapter_init();

    // // ESP_ERROR_CHECK is similar to assert. If arg of ESP_ERR_CHECK != ESP_ok, then err msg is printed and abort() is called
    // ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL));

    wifi_config_t wifi_cfg = {
        .sta = {
            .ssid = WIFI_USER,
            .password = WIFI_PASS
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());


    // need to wait and confirm that esp is actually connected to wifi before unregistering events
    // ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler));
    // ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler));

}


void app_main() {
    // nvs_flash_init();

    // for grabbing IP info of the esp chip
    tcpip_adapter_init();

    // ESP_ERROR_CHECK is similar to assert. If arg of ESP_ERR_CHECK != ESP_ok, then err msg is printed and abort() is called
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    connect_to_wifi();

    // only attemp connection AFTER we know for sure wifi is connected!
    // connect_to_mqtt();

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
