/*
    dns_server.c - DNS hijacker (captive portal) for ESP-IDF 5.3.2+
*/

#include <globalVar.h>


bool dns_server_active = 0;
char dns_server_ssid[128] = "ZAIRE_SETTING";
char dns_server_bssid[128];
bool remote_pairing_requested_btn = 0;
bool device_sta_mac_requested = 0;
const char *DNS_TAG = "dns_server";
int dns_sock = -1;
TaskHandle_t dns_task_handle = NULL;

void dns_server_task(void *pvParameters) {
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(DNS_PORT),
        .sin_addr.s_addr = htonl(INADDR_ANY)
    };

    dns_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (dns_sock < 0) {
        ESP_LOGE(DNS_TAG, "Failed to create socket: errno %d", errno);
        vTaskDelete(NULL);
        return;
    }

    if (bind(dns_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        ESP_LOGE(DNS_TAG, "Socket bind failed: errno %d", errno);
        close(dns_sock);
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(DNS_TAG, "DNS server started on port %d", DNS_PORT);

    uint8_t rx_buf[512];
    struct sockaddr_in source_addr;
    socklen_t socklen = sizeof(source_addr);

    while (1) {
        int len = recvfrom(dns_sock, rx_buf, sizeof(rx_buf), 0, (struct sockaddr *)&source_addr, &socklen);
        if (len < 12) continue; // Not a valid DNS header

        char hostname[256] = {0};
        int idx = 12, host_idx = 0;
        while (idx < len && rx_buf[idx] != 0 && host_idx < sizeof(hostname) - 1) {
            int seg_len = rx_buf[idx++];
            if ((idx + seg_len) >= len) break;
            if (host_idx != 0) hostname[host_idx++] = '.';
            memcpy(&hostname[host_idx], &rx_buf[idx], seg_len);
            host_idx += seg_len;
            idx += seg_len;
        }
        hostname[host_idx] = '\0';

        ESP_LOGI(DNS_TAG, "Intercepted DNS query for: %s", hostname);

        uint8_t tx_buf[512] = {0};
        memcpy(tx_buf, rx_buf, len);
        tx_buf[2] |= 0x80;
        tx_buf[3] = 0x80;
        tx_buf[7] = 1;

        int resp_idx = len;
        tx_buf[resp_idx++] = 0xC0;
        tx_buf[resp_idx++] = 0x0C;
        tx_buf[resp_idx++] = 0x00; tx_buf[resp_idx++] = 0x01; // Type A
        tx_buf[resp_idx++] = 0x00; tx_buf[resp_idx++] = 0x01; // Class IN
        tx_buf[resp_idx++] = 0x00; tx_buf[resp_idx++] = 0x00;
        tx_buf[resp_idx++] = 0x01; tx_buf[resp_idx++] = 0x2C; // TTL 300s
        tx_buf[resp_idx++] = 0x00; tx_buf[resp_idx++] = 0x04;

        esp_netif_ip_info_t ip;
        esp_netif_t* netif = esp_netif_get_handle_from_ifkey("WIFI_AP_DEF");
        esp_netif_get_ip_info(netif, &ip);
        tx_buf[resp_idx++] = ip.ip.addr & 0xFF;
        tx_buf[resp_idx++] = (ip.ip.addr >> 8) & 0xFF;
        tx_buf[resp_idx++] = (ip.ip.addr >> 16) & 0xFF;
        tx_buf[resp_idx++] = (ip.ip.addr >> 24) & 0xFF;

        sendto(dns_sock, tx_buf, resp_idx, 0, (struct sockaddr *)&source_addr, sizeof(source_addr));
    }

    close(dns_sock);
    vTaskDelete(NULL);
}

void start_dns_server(void) {
    wifi_settings_mode();  // Ensure Wi-Fi is set to AP mode
    if (dns_task_handle == NULL) {
        xTaskCreate(dns_server_task, "dns_server", DNS_TASK_STACK_SIZE, NULL, DNS_TASK_PRIORITY, &dns_task_handle);
        gpio_set_level(DISPLAY_EN_PIN, HIGH);
        display_target = DISPLAY_SHOW_DNS_SETTING;
        web_server = start_webserver();  // make sure start_webserver() returns httpd_handle_t
        if (web_server) {
            register_dns_catch_all(web_server);  // your handler to redirect all HTTP to settings page
            
        }

        ESP_LOGI(DNS_TAG, "DNS + Web server started");
    }
}

esp_err_t stop_dns_server(void) {
    char http_server_stop[512];
    wifi_standard_mode();  // Switch back to standard Wi-Fi mode -- for remote use in HELMET DEVICE

    snprintf(http_server_stop, sizeof(http_server_stop), "%s\n", HTTP_SERVER_CLOSE);
    h3_uart_send_data(http_server_stop);
    if (dns_task_handle != NULL) {
        // Stop DNS task
        vTaskDelete(dns_task_handle);
        dns_task_handle = NULL;
        ESP_LOGI(DNS_TAG, "DNS task killed");

        // Close DNS socket
        if (dns_sock >= 0) {
            close(dns_sock);
            dns_sock = -1;
            ESP_LOGI(DNS_TAG, "DNS socket closed");
        }

        // Stop web server
        if (web_server) {
            httpd_stop(web_server);
            web_server = NULL;
            ESP_LOGI(DNS_TAG, "Web server stopped");
        }

       

        return ESP_OK;
    }

    ESP_LOGW(DNS_TAG, "DNS server wasn't running");
    return ESP_FAIL;
}

esp_err_t portal_handler(httpd_req_t *req) {
    return main_page_get_handler(req);
}

void register_dns_catch_all(httpd_handle_t server) {
     httpd_uri_t catch_all = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = portal_handler,
        .user_ctx = NULL
    };
    httpd_register_uri_handler(server, &catch_all);

     const char *paths[] = {
        "/generate_204",
        "/hotspot-detect.html",
        "/success.txt",
        "/success.txt?ipv4",
        "/canonical.html"
    };

    for (int i = 0; i < sizeof(paths)/sizeof(paths[0]); i++) {
        httpd_uri_t uri = {
            .uri = paths[i],
            .method = HTTP_GET,
            .handler = portal_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &uri);
    }
}
