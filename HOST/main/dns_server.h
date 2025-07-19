#ifndef DNS_SERVER_H
#define DNS_SERVER_H

#include "esp_http_server.h"
#include "lwip/sockets.h"
#include "lwip/inet.h"

//DNS SERVER
extern char dns_server_ssid[128];
extern char dns_server_bssid[128];
#define DNS_PORT                53
#define DNS_TASK_STACK_SIZE     8192
#define DNS_TASK_PRIORITY       3

//HTTP SERVER
#define MAX_HTTP_RECV_BUFFER    512


#ifdef __cplusplus
extern "C" {
#endif
extern bool dns_server_active;
void start_dns_server(void);
esp_err_t stop_dns_server(void);
void register_dns_catch_all(httpd_handle_t server);


#ifdef __cplusplus
}
#endif

#endif // DNS_SERVER_H
