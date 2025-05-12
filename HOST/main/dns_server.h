#ifndef DNS_SERVER_H
#define DNS_SERVER_H

#include "esp_http_server.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"

#define DNS_PORT                53
#define DNS_TASK_STACK_SIZE     4096
#define DNS_TASK_PRIORITY       3

#ifdef __cplusplus
extern "C" {
#endif

void start_dns_server(void);
esp_err_t stop_dns_server(void);
void register_dns_catch_all(httpd_handle_t server);

#ifdef __cplusplus
}
#endif

#endif // DNS_SERVER_H
