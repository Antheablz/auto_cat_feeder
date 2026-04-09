/*
1) setup mDNS?
2) setup netbiosns_init();?
3) idf.py add-dependency joltwallet/LittleFS (small fail safe filesystem for microcontrollers, needed for frontend i think)

*/
#include "esp_log.h"
#include "mdns.h"
#include "esp_http_server.h"
#include "esp_event.h"

#include "server.h"

void start_rest_server() {
    
    // Generate default configuration
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    // Empty handle to http_server
    httpd_handle_t server = NULL;

    config.uri_match_fn = httpd_uri_match_wildcard;

    // ESP_ERROR_CHECK(httpd_start(&server, &config));

    if (httpd_start(&server, &config) == ESP_OK) {
        printf("-----> Server Started??\n");
        //now we register uri handlers
    }
}