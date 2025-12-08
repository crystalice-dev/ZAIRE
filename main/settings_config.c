#include <globalVar.h>


static const char *SET_TAG = "settings";

// Exported so dns_server.c can reference it
httpd_handle_t web_server = NULL;

/* ===== Index File Handlers ===== */

static esp_err_t hello_post_handler(httpd_req_t *req)
{
    // (Optional) read the body if you expect data
    // char buf[64]; int len = httpd_req_recv(req, buf, MIN(req->content_len, sizeof(buf)));

    printf("hello World\n");           // <-- your request
    // ESP_LOGI(TAG, "hello World");   // (nicer logging)

    httpd_resp_set_type(req, "text/plain");
    return httpd_resp_sendstr(req, "OK");
}

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

// Optional: avoid 404 spam from favicon requests
static esp_err_t favicon_handler(httpd_req_t *req)
{
    httpd_resp_set_type(req, "image/x-icon");
    // Tiny 1×1 empty response
    return httpd_resp_send(req, "", 0);
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

esp_err_t globalData_handler(httpd_req_t *req){
    FILE *f = fopen("/spiffs/globalData.js", "r");
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

esp_err_t style_handler(httpd_req_t *req){
    FILE *f = fopen("/spiffs/style.css", "r");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char line[256];
    httpd_resp_set_type(req, "text/css");
    while (fgets(line, sizeof(line), f)) {
        httpd_resp_sendstr_chunk(req, line);
    }

    fclose(f);
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

esp_err_t logo_handler(httpd_req_t *req)
{
    char full_path[1024];
    snprintf(full_path, sizeof(full_path), "/spiffs/photo_%d.jpg",30); 
    const char *path = "/spiffs/photo_30.jpg";

    FILE *f = fopen(path, "rb");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "image/png");
    httpd_resp_set_hdr(req, "Cache-Control", "public, max-age=86400"); // optional

    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        if (httpd_resp_send_chunk(req, buf, n) != ESP_OK) {
            fclose(f);
            httpd_resp_sendstr_chunk(req, NULL); // end chunked transfer
            return ESP_FAIL;
        }
    }
    fclose(f);
    httpd_resp_sendstr_chunk(req, NULL); // end chunked transfer
    return ESP_OK;
}

/* ====== DASHBOARD FILES Handlers ===== */

esp_err_t dashboard_screen_page_get_handler(httpd_req_t *req)
{

    FILE *index = fopen("/spiffs/www/homeScreen.html", "r");
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

esp_err_t dashboard_js_handler(httpd_req_t *req){
    FILE *f = fopen("/spiffs/www/data.js", "r");
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

esp_err_t dashboard_style_handler(httpd_req_t *req){
    FILE *f = fopen("/spiffs/www/dashStyle.css", "r");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char line[256];
    httpd_resp_set_type(req, "text/css");
    while (fgets(line, sizeof(line), f)) {
        httpd_resp_sendstr_chunk(req, line);
    }

    fclose(f);
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

/* ===== MAIN URI table ===== */

httpd_uri_t main_page = { .uri = "/", .method = HTTP_GET, .handler = main_page_get_handler, .user_ctx = NULL };
httpd_uri_t favicon_uri = {.uri = "/favicon.ico", .method = HTTP_GET, .handler = favicon_handler, .user_ctx = NULL};
httpd_uri_t script_handler = {.uri = "/script.js", .method = HTTP_GET,.handler = js_handler,.user_ctx = NULL};
httpd_uri_t css_handler = {.uri = "/style.css", .method = HTTP_GET,.handler = style_handler,.user_ctx = NULL};
httpd_uri_t logo_uri = { .uri = "/crystal-ice-logo.png", .method = HTTP_GET, .handler = logo_handler, .user_ctx = NULL};
httpd_uri_t hello = { .uri = "/hello", .method = HTTP_POST, .handler = hello_post_handler, .user_ctx = NULL};
httpd_uri_t globalData_js = { .uri = "/globalData.js", .method = HTTP_GET, .handler = globalData_handler, .user_ctx = NULL};

/* ===== DASHBOARD URI table ===== */
httpd_uri_t dashboard_screen_page = { .uri = "/wwww/homeScreen.html", .method = HTTP_GET, .handler = dashboard_screen_page_get_handler, .user_ctx = NULL };
httpd_uri_t dashboard_js = {.uri = "/wwww/data.js", .method = HTTP_GET,.handler = dashboard_js_handler,.user_ctx = NULL};
httpd_uri_t dashboard_css = {.uri = "/wwww/dashStyle.css", .method = HTTP_GET,.handler = dashboard_style_handler,.user_ctx = NULL};

/* ===== Server start ===== */

httpd_handle_t start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;
    config.lru_purge_enable = true;
    config.uri_match_fn = httpd_uri_match_wildcard;   // needed**

    if (httpd_start(&web_server, &config) == ESP_OK) {
        httpd_register_uri_handler(web_server, &main_page);
        httpd_register_uri_handler(web_server, &favicon_uri);
        httpd_register_uri_handler(web_server, &script_handler);
        httpd_register_uri_handler(web_server, &css_handler);
        httpd_register_uri_handler(web_server, &logo_uri);
        httpd_register_uri_handler(web_server, &hello);
        httpd_register_uri_handler(web_server, &globalData_js);
        httpd_register_uri_handler(web_server, &dashboard_screen_page);
        httpd_register_uri_handler(web_server, &dashboard_js);
        httpd_register_uri_handler(web_server, &dashboard_css);
      
        ESP_LOGI(SET_TAG, "Web server started (serving embedded Hello World)");
        return web_server;
    }

    ESP_LOGE(SET_TAG, "Web server start failed");
    return NULL;
}
