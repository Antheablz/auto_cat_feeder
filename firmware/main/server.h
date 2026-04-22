#ifndef SERVER_H
#define SERVER_H

#include "esp_http_server.h"

esp_err_t webpage_css_handler(httpd_req_t *req)
esp_err_t webpage_html_handler(httpd_req_t *req);
void initialize_fs(void);
void initialize_mdns(void);
void start_rest_server(void);

#endif /* SERVER_H */