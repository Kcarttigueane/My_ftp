/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** help.c
*/

#include "../../include/server.h"

void help_all_commands(int control_socket)
{
    char* message = my_strcat(FTP_REPLY_214, COMMANDS);
    dprintf(control_socket, "%s%s", FTP_REPLY_214, COMMANDS);
    free(message);
}

void help_one_command(int control_socket, char** input_command)
{
    for (size_t i = 0; i < COMMANDS_DATA_SIZE; i++) {
        if (!strcasecmp(input_command[1], COMMANDS_DATA[i].name)) {
            char* message =
                my_strcat(FTP_REPLY_214, COMMANDS_DATA[i].description);
            write(control_socket, message, strlen(message));
            free(message);
            return;
        }
    }
    send_resp(control_socket, FTP_REPLY_500);
}

void help_command(int control_socket, ...)
{
    va_list args;
    va_start(args, control_socket);

    client_t* clients = get_nth_argument(1, args);

    if (!is_logged(control_socket, clients, &args))
        return;

    char** input_command = get_nth_argument(2, args);
    int size = get_size_word_array(input_command);

    (size > 1) ? help_one_command(control_socket, input_command)
    : help_all_commands(control_socket);

    va_end(args);
}
