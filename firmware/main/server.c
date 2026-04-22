/*
1) setup mDNS?
2) setup netbiosns_init();?
3) idf.py add-dependency joltwallet/LittleFS (small fail safe filesystem for microcontrollers, needed for frontend i think)

*/
#include <string.h>
#include <fcntl.h>
#include "esp_log.h"
#include "mdns.h"
#include "esp_http_server.h"
#include "esp_event.h"
#include "esp_littlefs.h"
#include "lwip/apps/netbiosns.h"

#include "server.h"
#include "constants.h"

#define SCRATCH_BUFSIZE 1024

static char scratch[SCRATCH_BUFSIZE];

esp_err_t serve_files(const char *filepath, httpd_req_t *req) {

    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to open file");
        return ESP_FAIL;
    }

    ssize_t bytes_read = 0;
    while ((bytes_read = read(fd, scratch, SCRATCH_BUFSIZE)) > 0) {

        if (httpd_resp_send_chunk(req, scratch, bytes_read) != ESP_OK) {
            close(fd);
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to read file");
            return ESP_FAIL;
        }

    }

    close(fd);
    httpd_resp_send_chunk(req, NULL, 0);

    return ESP_OK;
}

esp_err_t webpage_css_handler(httpd_req_t *req) {
    esp_err_t ret = ESP_OK;

    ESP_ERROR_CHECK(httpd_resp_set_type(req, "text/css"));
    ret = serve_files(CSS_FILE_PATH, req);

    printf("-----> Served CSS File\n");
    return ret;
}

esp_err_t webpage_html_handler(httpd_req_t *req) {
    esp_err_t ret = ESP_OK;

    ESP_ERROR_CHECK(httpd_resp_set_type(req, "text/html"));
    ret = serve_files(INDEX_FILE_PATH, req);

    printf("-----> Served HTML File\n");
    return ret;
}

void initialize_fs() {
   esp_vfs_littlefs_conf_t conf = {
    .base_path = BASE_PATH,
    .partition_label = PARTITION_LABEL,
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
        //return an error. eventually set xEventGroupWaitBits thing or event off?
        //look into the built in esp_http_server_event_id_t for event handling??
    }

    printf("-----> Server Started\n");

    //now we register uri handlers
    /* URI handler for getting web server html file */
    httpd_uri_t webpage_html_uri= {
        .uri        = "/",
        // .uri        = "/index.html",
        .method     = HTTP_GET,
        .handler    = webpage_html_handler,
        .user_ctx   = NULL
    };
    httpd_register_uri_handler(server, &webpage_html_uri);


    /* URI handler for getting  web server css file */
    httpd_uri_t webpage_css_uri= {
        .uri        = "/style.css",
        .method     = HTTP_GET,
        .handler    = webpage_css_handler,
        .user_ctx   = NULL
    };
    httpd_register_uri_handler(server, &webpage_css_uri);


    /* URI handler for turning LED on and off */
}