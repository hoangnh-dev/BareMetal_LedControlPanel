#include "led_cmd.h"
#include "led.h"
#include <stddef.h>

static int32_t cmd_led_set(uint8_t index) {
    uint8_t mode = index - 1;
    if (mode >= LED_MODE_COUNT) return CMD_INVALID;
    led_set_mode((led_mode_t)mode);
    return CMD_SUCCESS;
}

const cmd_t led_table[] = {
    {"1", cmd_led_set, "OFF"},
    {"2", cmd_led_set, "ON"},
    {"3", cmd_led_set, "Blink Slow"},
    {"4", cmd_led_set, "Blink Fast"},
    {NULL, NULL, NULL}
};