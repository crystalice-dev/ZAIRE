#include "globalVar.h"

const char *TAG_DNS = "WEB-SERVER";
httpd_handle_t web_server = NULL;


/* === MAIN HTML PAGE === */
esp_err_t hello_get_handler(httpd_req_t *req)
{
    FILE *f = fopen("/spiffs/index.html", "r");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char line[256];
    httpd_resp_set_type(req, "text/html");
    while (fgets(line, sizeof(line), f)) {
        httpd_resp_sendstr_chunk(req, line);
    }
    fclose(f);
    httpd_resp_sendstr_chunk(req, NULL); // Signal end of chunked response
    return ESP_OK;
}

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

esp_err_t ping_handler(httpd_req_t *req)
{
    printf("hello from button\n");
    httpd_resp_set_type(req, "text/plain");
    httpd_resp_sendstr(req, "pong!");
    return ESP_OK;
}

httpd_uri_t hello = { .uri = "/", .method = HTTP_GET, .handler = hello_get_handler, .user_ctx = NULL };
httpd_uri_t update = { .uri = "/update", .method = HTTP_POST, .handler = update_post_handler, .user_ctx = NULL };
httpd_uri_t ping = { .uri = "/ping", .method = HTTP_GET, .handler = ping_handler, .user_ctx = NULL };

httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;
    config.lru_purge_enable = true;

    if (httpd_start(&web_server, &config) == ESP_OK) {
        httpd_register_uri_handler(web_server, &hello);
        httpd_register_uri_handler(web_server, &update);
        httpd_register_uri_handler(web_server, &ping);
        ESP_LOGI(TAG_DNS, "Web server started");
        return web_server;
    } else {
        ESP_LOGE(TAG_DNS, "Failed to start server");
        return NULL;
    }
}


esp_err_t expose_main_menu_page(void);
esp_err_t expose_close_settings_page(void);