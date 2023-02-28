/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** parse_commands.c
*/

#include "./../include/server.h"

void parse_command(circular_buffer* cb, server_data_t* server_data,
int control_socket, client_t* clients)
{
    char** command = cb_pop_command(cb);
    debug_word_array(command);

    if (command == NULL) {
        send_resp(control_socket, FTP_REPLY_500);
        return;
    }

    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcasecmp(command[0], COMMANDS_DATA[i].name)) {
            list_args_t args = {.control_socket = control_socket,
                                .server_data = server_data,
                                .input_command = command,
                                .clients = clients};
            command_func_t func = COMMANDS_DATA[i].func;
            func(&args);
            free_word_array(command);
            return;
        }
    }
    send_resp(control_socket, FTP_REPLY_500);
    free_word_array(command);
}
