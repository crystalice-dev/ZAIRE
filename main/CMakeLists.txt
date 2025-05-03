idf_component_register(
    SRCS 
        "display_config.c"
        "html_config.c"
        "nvs_config.c" 
        "network_config.c" 
        "dns_server.c" 
        "settings_config.c" 
        "SuperMon.c" 
        "gpio_config.c" 
        "uart_config.c" 
        "remote_config.c" 
        "usb_mic_config.c" 
        "zaire_system.c" 
        "main.c"
    INCLUDE_DIRS "."
)

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
