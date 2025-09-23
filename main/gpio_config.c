#include <globlaVar.h>


esp_err_t init_gpio(){

    gpio_config_t walkie_btn_config = {
        .pin_bit_mask = (1ULL << WALKIE_BTN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    if(gpio_config(&walkie_btn_config) != ZAIRE_OK)return ZAIRE_FAIL;

    gpio_config_t purpose_left_btn_config = {
        .pin_bit_mask = (1ULL << PURPOSE_LEFT),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    if(gpio_config(&purpose_left_btn_config) != ZAIRE_OK)return ZAIRE_FAIL;

    gpio_config_t purpose_right_btn_config = {
        .pin_bit_mask = (1ULL << PURPOSE_RIGHT),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    if(gpio_config(&purpose_right_btn_config) != ZAIRE_OK)return ZAIRE_FAIL;

    gpio_config_t bk3266_pp_call_config = {
        .pin_bit_mask = (1ULL << BK3266_PP_CALL),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    if(gpio_config(&bk3266_pp_call_config) != ZAIRE_OK)return ZAIRE_FAIL;

    return ZAIRE_OK;
}