idf_component_register(SRCS 
            "peer_mesh_config.c"
            "settings_config.c"
            "dns_server.c"
            "buzzer_config.c"
            "network_config.c"
            "BK3266_config.c"
            "MAX17043_config.c"
            "display_config.c"
            "task_config.c"
            "uart_config.c"
            "gpio_config.c"
            "walkie_config.c"
            "camera_config.c"
            "zaire_system.c"
            "main.c"
            INCLUDE_DIRS ".")

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
