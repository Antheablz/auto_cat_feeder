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

esp_err_t webpage_files_handler(httpd_req_t *req)
{
    // Handle the request
    // ...

    // Return ESP_OK if the request was handled successfully
    return ESP_OK;

    // Return an error code to close the connection
    // return ESP_FAIL;
}

void start_rest_server() {
    
    // Generate default configuration
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    // Empty handle to http_server
    httpd_handle_t server = NULL;

    config.uri_match_fn = httpd_uri_match_wildcard;

    // ESP_ERROR_CHECK(httpd_start(&server, &config));

    if (httpd_start(&server, &config) != ESP_OK) {
        printf("-----> Server failed to start!\n");
        //free rest_context var
        //return an error. eventually set xEventGroupWaitBits thing or event off?
        //look into the built in esp_http_server_event_id_t for event handling??
    }

    printf("-----> Server Started\n");

    //now we register uri handlers
    /* URI handler for getting web server files */
    httpd_uri_t webpage_files_uri= {
        .uri        = "/*",
        .method     = HTTP_GET,
        .handler    = webpage_files_handler,
        .user_ctx   = NULL
    };
    httpd_register_uri_handler(server, &webpage_files_uri);

    /* URI handler for turning LED on and off */
}