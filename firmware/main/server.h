#ifndef SERVER_H
#define SERVER_H

#include "esp_http_server.h"

esp_err_t webpage_files_handler(httpd_req_t *req);
void start_rest_server(void);

#endif /* SERVER_H */