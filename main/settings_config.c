#include <globalVar.h>


static const char *SET_TAG = "settings";

// Exported so dns_server.c can reference it
httpd_handle_t web_server = NULL;

/* ===== Index File Handlers ===== */

static esp_err_t settings_fetch_onLoad_data_handler(httpd_req_t *req) // Handle init data fetching from settings page
{
    char settings_data[256] = {0};

    int len = snprintf(settings_data, sizeof(settings_data),
        "user_name=%s&device_name=%s"
        "&lang=%d&units=%d&theme=%d"
        "&lower_bt_vol=%d&auto_bt=%d"
        "&auto_record=%d&mute_record_audio=%d"
        "&photos=%u&walkie_peers=%u"
        "&bt_connected=%d&bt_name=%s&top_speed=%.1f",

        g_user_prefs.user_name,
        g_user_prefs.device_name,

        g_system_prefs.device_lang,
        g_system_prefs.units,
        g_system_prefs.theme,
        g_system_prefs.lower_bt_volume_on_walkie,
        g_system_prefs.auto_bt_on_powerup,
        g_system_prefs.device_auto_record,
        g_system_prefs.device_mute_record_audio,

        g_device_state.photos_count,
        g_device_state.walkie_peers_count,
        g_device_state.bt_connected,
        g_device_state.bt_device_name,
        g_device_state.top_speed
    );

    // This will save your ass one day
    if (len >= sizeof(settings_data)) {
        ESP_LOGE("HTTP", "Settings response truncated! Needed %d bytes, had %d", len, (int)sizeof(settings_data));
        return httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Config overflow");
    }

    httpd_resp_set_type(req, "text/plain");
    return httpd_resp_sendstr(req, settings_data);
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


esp_err_t httpd_serve_static_files(httpd_req_t *req) {
    char filepath[128];  // Buffer for full SPIFFS path
    const char *uri_path = req->uri + strlen("/media/photos/");  // Skip prefix to get relative path (e.g., "photo_0.jpg")

    // Basic security: Prevent directory traversal (reject ".." or absolute paths)
    if (strstr(uri_path, "..") || uri_path[0] == '/') {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    // Build full SPIFFS path (e.g., "/spiffs/media/photos/photo_0.jpg")
    snprintf(filepath, sizeof(filepath), "/spiffs/media/photos/%s", uri_path);

    // Open the file
    int fd = open(filepath, O_RDONLY, 0);
    if (fd == -1) {
        ESP_LOGE("HTTP", "Failed to open file: %s", filepath);
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    // Get file size
    struct stat st;
    if (fstat(fd, &st) != 0) {
        close(fd);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    // Set content type based on extension (optional but good for images)
    const char *ext = strrchr(uri_path, '.');
    if (ext) {
        if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
            httpd_resp_set_type(req, "image/jpeg");
        } else if (strcmp(ext, ".png") == 0) {
            httpd_resp_set_type(req, "image/png");
        }  // Add more if needed (e.g., .gif, .css, .js)
    }

    // Send file in chunks to avoid large malloc (safe for big photos)
    char buf[1024];
    ssize_t read_bytes;
    esp_err_t err = ESP_OK;
    while ((read_bytes = read(fd, buf, sizeof(buf))) > 0) {
        if (httpd_resp_send_chunk(req, buf, read_bytes) != ESP_OK) {
            err = ESP_FAIL;
            break;
        }
    }
    close(fd);

    if (read_bytes < 0) {
        err = ESP_FAIL;
    }

    // End response
    httpd_resp_send_chunk(req, NULL, 0);
    return err;
}


/* ===== MAIN URI table ===== */

httpd_uri_t main_page = { .uri = "/", .method = HTTP_GET, .handler = main_page_get_handler, .user_ctx = NULL };
httpd_uri_t favicon_uri = {.uri = "/favicon.ico", .method = HTTP_GET, .handler = favicon_handler, .user_ctx = NULL};
httpd_uri_t script_handler = {.uri = "/script.js", .method = HTTP_GET,.handler = js_handler,.user_ctx = NULL};
httpd_uri_t css_handler = {.uri = "/style.css", .method = HTTP_GET,.handler = style_handler,.user_ctx = NULL};
httpd_uri_t logo_uri = { .uri = "/crystal-ice-logo.png", .method = HTTP_GET, .handler = logo_handler, .user_ctx = NULL};
httpd_uri_t globalData_js = { .uri = "/globalData.js", .method = HTTP_GET, .handler = globalData_handler, .user_ctx = NULL};

/* ===== DASHBOARD URI table ===== */
httpd_uri_t dashboard_screen_page = { .uri = "/www/homeScreen.html", .method = HTTP_GET, .handler = dashboard_screen_page_get_handler, .user_ctx = NULL };
httpd_uri_t dashboard_js = {.uri = "/www/data.js", .method = HTTP_GET,.handler = dashboard_js_handler,.user_ctx = NULL};
httpd_uri_t dashboard_css = {.uri = "/www/dashStyle.css", .method = HTTP_GET,.handler = dashboard_style_handler,.user_ctx = NULL};

/* ===== PHOTO URI table ===== */
httpd_uri_t photos_uri = {
    .uri      = "/media/photos/*",           // ← URL prefix the browser will use
    .method   = HTTP_GET,
    .handler  = httpd_serve_static_files,    // ← THIS IS THE BUILT-IN HANDLER
    .user_ctx = "/spiffs/media/photos"        // ← actual folder on SPIFFS
};

/* ===== DATA FETCHING ===== */
httpd_uri_t settings_fetch_onLoad_data = { .uri = "/settings_fetch_onLoad_data", .method = HTTP_POST, .handler = settings_fetch_onLoad_data_handler, .user_ctx = NULL};

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
        httpd_register_uri_handler(web_server, &settings_fetch_onLoad_data);
        httpd_register_uri_handler(web_server, &globalData_js);
        httpd_register_uri_handler(web_server, &dashboard_screen_page);
        httpd_register_uri_handler(web_server, &dashboard_js);
        httpd_register_uri_handler(web_server, &dashboard_css);
        httpd_register_uri_handler(web_server, &photos_uri);
      
        ESP_LOGI(SET_TAG, "Web server started (serving embedded Hello World)");
        return web_server;
    }

    ESP_LOGE(SET_TAG, "Web server start failed");
    return NULL;
}
