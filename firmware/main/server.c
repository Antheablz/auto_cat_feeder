/*
1) setup mDNS?
2) setup netbiosns_init();?
3) idf.py add-dependency joltwallet/LittleFS (small fail safe filesystem for microcontrollers, needed for frontend i think)

*/
#include "esp_log.h"
#include "mdns.h"
#include "esp_http_server.h"
#include "esp_event.h"
#include "esp_littlefs.h"
#include "lwip/apps/netbiosns.h"

#include "server.h"
#include "constants.h"

esp_err_t webpage_files_handler(httpd_req_t *req) {
    // Handle the request
    httpd_resp_send(req,"HI BEN <3", 9);

    // Return ESP_OK if the request was handled successfully
    return ESP_OK;

    // Return an error code to close the connection
    // return ESP_FAIL;
}

void initialize_fs() {
   esp_vfs_littlefs_conf_t conf = {
    .base_path = "/littlefs",
    .partition_label = "storage",
    .format_if_mount_failed = true
   };

   ESP_ERROR_CHECK(esp_vfs_littlefs_register(&conf));

   printf("-----> Registered the File System\n");
}

void initialize_mdns() {
    mdns_init();
    mdns_hostname_set(MDNS_HOSTNAME);
    // mdns_instance_name_set("tmp");

    ESP_ERROR_CHECK(mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0));
}

void start_rest_server() {
    initialize_mdns();
    netbiosns_init();
    netbiosns_set_name(MDNS_HOSTNAME);
    initialize_fs();

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
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