/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** parse_commands.c
*/

#include "./../include/server.h"

void* get_nth_argument(int n, va_list args)
{
    void* arg = NULL;
    for (int i = 0; i <= n; i++) {
        arg = va_arg(args, void*);
    }
    return arg;
}

void parse_command(circular_buffer* cb, server_data_t* server_data,
int control_socket, client_t* clients)
{
    char** command = cb_pop_command(cb);
    debug_word_array(command);

    if (command == NULL) {
        printf("command is null\n");
        return;
    }
    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcasecmp(command[0], COMMANDS_DATA[i].name)) {
            command_func_t func = COMMANDS_DATA[i].func;
            func(control_socket, server_data, clients, command);
            free_word_array(command);
            return;
        }
    }
    write(control_socket, FTP_REPLY_500, strlen(FTP_REPLY_500));
    free_word_array(command);
}
