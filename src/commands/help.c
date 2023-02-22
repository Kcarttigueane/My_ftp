/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** help.c
*/

#include "../../include/server.h"

void help_all_commands(int control_socket, char** input_command)
{
    char* message = my_strcat(FTP_REPLY_214, COMMANDS);
    printf("message = %s\n", message);
    write(control_socket, message, strlen(message));
    free(message);
}

void help_one_command(int control_socket, char** input_command)
{
    for (size_t i = 0; i < ARRAY_SIZE(COMMANDS); i++) {
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

void help_command(int control_socket, char** input_command)
{
    int size = get_size_word_array(input_command);

    (size > 1) ? help_one_command(control_socket, input_command)
    : help_all_commands(control_socket, input_command);
}
