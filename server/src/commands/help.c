/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** help.c
*/

#include "server.h"

const char COMMANDS[14][5] = {
    "HELP", "NOOP", "USER", "PASS", "CWD",  "CDUP", "QUIT",
    "DELE", "PWD",  "PASV", "PORT", "RETR", "STOR", "LIST",
};

void help_all_commands(int i, char** input_command)
{
    send_resp(i, FTP_REPLY_214);

    if (!input_command[1])
        help_one_command(i, input_command);
    else {
        for (int j = 0; j < 14; j++) {
            write(i, COMMANDS[j], strlen(COMMANDS[j]));
            write(i, " ", 1);
        }
    }

}

void help_one_command(int i, char** input_command)
{
    for (int i = 0; i < ARRAY_SIZE(COMMANDS); i++) {
        if (!strcasecmp(input_command[1], COMMANDS_DATA[i].name)) {
            printf("%s: %s\n", COMMANDS_DATA[i].name,
                   COMMANDS_DATA[i].description);
            return;
        }
    }
    send_resp(i, FTP_REPLY_500);
}
