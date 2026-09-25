#include "cmd.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static uint8_t cmd_validate(const cmd_t* table, const uint8_t* input) {
    if (table == NULL) return CMD_TBL_NOT_FOUND;
    if (input == NULL) return CMD_EMPTY;
    if (*input == '\0' || *input == '\n' || *input == '\r' || *input == ' ') return CMD_EMPTY;
    return CMD_SUCCESS;
}
static uint8_t cmd_validate_select(const uint8_t* input) {
	if (*input < '0' || *input > '9') return CMD_INVALID;
    return CMD_SUCCESS;
}

void cmd_print_error(uint8_t error_code) {
    switch (error_code) {
        case CMD_NOT_FOUND:     printf("[ERROR]: Command not found\r\n");   break;
        case CMD_EMPTY:         printf("[ERROR]: Empty command\r\n");        break;
        case CMD_TOO_LONG:      printf("[ERROR]: Command too long\r\n");     break;
        case CMD_TBL_NOT_FOUND: printf("[ERROR]: Table not found\r\n");      break;
        default: break;
    }
}

void cmd_print_menu(const cmd_t* table) {
    const cmd_t* p = table;
    uint8_t i = 1;
    printf("====== MENU ======\r\n");
    while (p->cmd) {
        printf("[%d] %s - %s\r\n", i, p->cmd, p->info);
        i++;
        p++;
    }
    printf("==================\r\n");
    printf("> Enter your selection:\r\n ");
}

uint8_t cmd_select_menu(const cmd_t* table, uint8_t* input) {
	uint8_t ret = cmd_validate(table, input);
    if (ret != CMD_SUCCESS) return ret;

    uint8_t check = cmd_validate_select(input);
    if (check != CMD_SUCCESS) return check;

    uint8_t index = atoi((char*)input);

    uint8_t i = 1;
    while (table->cmd) {
        if (i == index) {
            int32_t result = table->func(index);
            if (result == CMD_EXIT) return CMD_EXIT;
            return CMD_SUCCESS;
        }
        i++;
        table++;
    }
    return CMD_NOT_FOUND;
}
uint8_t cmd_run_menu(const cmd_t* table) {
    cmd_print_menu(table);
    uint8_t input = '0';
    uint8_t result = cmd_select_menu(table, &input);
    cmd_print_error(result);
    return result;
}