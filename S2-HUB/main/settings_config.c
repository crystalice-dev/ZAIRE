#include "globalVar.h"

const char *TAG_DNS = "WEB-SERVER";
httpd_handle_t web_server = NULL;


/* === MAIN HTML PAGE === */

esp_err_t update_post_handler(httpd_req_t *req)
{
    char buf[256];
    int ret, remaining = req->content_len;

    ESP_LOGI("POST", "Handling settings POST...");
    memset(buf, 0, sizeof(buf));

    while (remaining > 0) {
        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf) - 1))) <= 0) {
            return ESP_FAIL;
        }
        remaining -= ret;
    }

    buf[sizeof(buf) - 1] = '\0';
    ESP_LOGI("POST", "Received form data: %s", buf);

    httpd_resp_set_type(req, "text/plain");
    httpd_resp_sendstr(req, "Settings received successfully!");
    return ESP_OK;
}

esp_err_t device_info_handler(httpd_req_t *req){
    
    static char info[1040]; // DEVICE_TYPE-DEVCE_NAME

    snprintf(info,sizeof(info), "%d-%s-%s-%d-%d-{%s %s}-%s-%d", DEVICE_TYPE, DEVICE_NAME, WIFI_SSID, WALKIE_STATUS, BATTERY_STATUS, gps_latitude, gps_longitude, gps_elevation, TEMP_STATUS);
    printf("%s\n", info);

    httpd_resp_set_type(req, "text/plain");
    httpd_resp_sendstr(req, "pong!");
    return ESP_OK;
}

//PAGEs

httpd_uri_t update = { .uri = "/update", .method = HTTP_POST, .handler = update_post_handler, .user_ctx = NULL };
httpd_uri_t device_info = { .uri = "/device_info", .method = HTTP_GET, .handler = device_info_handler, .user_ctx = NULL };

//FILEs
esp_err_t main_page_get_handler(httpd_req_t *req)
{
    FILE *index = fopen("/spiffs/index.html", "r");
    if (!index) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char line[256];
    httpd_resp_set_type(req, "text/html");
    while (fgets(line, sizeof(line), index)) {
        httpd_resp_sendstr_chunk(req, line);
    }

    fclose(index);
    httpd_resp_sendstr_chunk(req, NULL); // Signal end of chunked response
    return ESP_OK;
}

esp_err_t js_handler(httpd_req_t *req){
    FILE *f = fopen("/spiffs/script.js", "r");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char line[256];
    httpd_resp_set_type(req, "application/javascript");
    while (fgets(line, sizeof(line), f)) {
        httpd_resp_sendstr_chunk(req, line);
    }

    fclose(f);
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

esp_err_t css_handler(httpd_req_t *req){
    FILE *f = fopen("/spiffs/style.css", "r");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char line[256];
    httpd_resp_set_type(req, "application/css");
    while (fgets(line, sizeof(line), f)) {
        httpd_resp_sendstr_chunk(req, line);
    }

    fclose(f);
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

httpd_uri_t main_page = { .uri = "/", .method = HTTP_GET, .handler = main_page_get_handler, .user_ctx = NULL };
httpd_uri_t script_handler = {.uri = "/script.js", .method = HTTP_GET,.handler = js_handler,.user_ctx = NULL};
httpd_uri_t _handler = {.uri = "/style.css", .method = HTTP_GET,.handler = js_handler,.user_ctx = NULL};

httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;
    config.lru_purge_enable = true;

    if (httpd_start(&web_server, &config) == ESP_OK) {
        httpd_register_uri_handler(web_server, &main_page);
        httpd_register_uri_handler(web_server, &update);
        httpd_register_uri_handler(web_server, &device_info);
        httpd_register_uri_handler(web_server, &script_handler);
        ESP_LOGI(TAG_DNS, "Web server started");
        return web_server;
    } else {
        ESP_LOGE(TAG_DNS, "Failed to start server");
        return NULL;
    }
}
