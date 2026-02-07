/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"




void app_main() {

    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_NUM_12),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    gpio_config(&io_conf);

    esp_err_t ret;
    int level;

    while(1) {
        ret = gpio_set_level(GPIO_NUM_12, 1);
        level = gpio_get_level(GPIO_NUM_12);
        printf("LED ON - level: %d\n", level);

        vTaskDelay(1000 / portTICK_RATE_MS);

        ret = gpio_set_level(GPIO_NUM_12, 0);
        level = gpio_get_level(GPIO_NUM_12);
        printf("LED OFF - level: %d\n", level);

        vTaskDelay(1000 / portTICK_RATE_MS);

        
    }

}


// void app_main()
// {
//     printf("Hello world!\n");

//     /* Print chip information */
//     esp_chip_info_t chip_info;
//     esp_chip_info(&chip_info);
//     printf("This is ESP8266 chip with %d CPU cores, WiFi, ",
//             chip_info.cores);

//     printf("silicon revision %d, ", chip_info.revision);

//     printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
//             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

//     for (int i = 10; i >= 0; i--) {
//         printf("Restarting in %d seconds...\n", i);
//         vTaskDelay(1000 / portTICK_PERIOD_MS);
//     }
//     printf("Restarting now.\n");
//     fflush(stdout);
//     esp_restart();
// }
