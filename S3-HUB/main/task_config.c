#include <globalVar.h>

TaskHandle_t gpio_task_handler = NULL;
TaskHandle_t host_task_handler = NULL;
TaskHandle_t bk_task_handler = NULL;
TaskHandle_t h3_task_handler = NULL;
TaskHandle_t i2c_task_handler = NULL;

void host_run_task(void *vpParam) {
    uint8_t host_data[BUF_SIZE];

    while (1) {
        // Read from HOST UART
        int host_len = uart_read_bytes(HOST_UART_NUM, host_data, BUF_SIZE, pdMS_TO_TICKS(100));

        if (host_len > 0) {
            // Directly write the raw bytes to H3 UART
            uart_write_bytes(H3_UART_NUM, (const char *)host_data, host_len);

            // Optional: flush output if needed
            uart_wait_tx_done(H3_UART_NUM, pdMS_TO_TICKS(50));

            // Optional: log received data as null-terminated string
            if (host_len < BUF_SIZE) host_data[host_len] = '\0';
            // printf("Forwarded: %s\n", (char *)host_data);
        }

        // Prevent CPU hogging (adjust delay as needed)
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}


void bk_run_task(void *vpParam) {
    uint8_t bk_data[BUF_SIZE];

    while (1) {
        int bk_len = uart_read_bytes(HOST_UART_NUM, bk_data, BUF_SIZE, pdMS_TO_TICKS(100));

        if (bk_len > 0) {
            // Directly write the raw bytes to H3 UART
            printf("%s\n",(const char *)bk_data);

            // Optional: log received data as null-terminated string
            if (bk_len < BUF_SIZE) bk_data[bk_len] = '\0';
            // printf("Forwarded: %s\n", (char *)host_data);
        }

        // Prevent CPU hogging (adjust delay as needed)
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}


void h3_run_task(void *vpParam) {
    uint8_t h3_data[BUF_SIZE];

    while (1) {
        // Read from HOST UART
        int host_len = uart_read_bytes(H3_UART_NUM, h3_data, BUF_SIZE, pdMS_TO_TICKS(100));

        if (host_len > 0) {
            printf("%s\n",(const char *)h3_data);

            // Optional: log received data as null-terminated string
            if (host_len < BUF_SIZE) h3_data[host_len] = '\0';
            // printf("Forwarded: %s\n", (char *)host_data);
        }

        // Prevent CPU hogging (adjust delay as needed)
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}