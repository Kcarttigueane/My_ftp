/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** commands_data.c
*/

#include "../../include/server.h"

const command_t COMMANDS_DATA[] = {
    {"HELP", "List available commands\r\n", help_command},
    {"NOOP", "Do nothing\r\n", noop},
    {"USER", "Specify user for authentication\r\n", user},
    {"PASS", "Specify password for authentication\r\n", pass},
    {"CWD", "Change working directory\r\n", cwd_command},
    {"CDUP", "Change working directory to parent directory\r\n", cdup},
    {"QUIT", "Disconnection\r\n", NULL},
    {"DELE", "Delete file on the server\r\n", dele},
    {"PWD", "Print working directory\r\n", pwd},
    {"PASV", "Enable \"passive\" mode for data transfer\r\n", pasv},
    {"PORT", "Enable \"active\" mode for data transfer\r\n", NULL},
    {"RETR", "Download file from the server to the client\r\n", NULL},
    {"STOR", "Upload file from the client to the server\r\n", NULL},
    {"LIST", "List files in the current working directory\r\n", list},
};

const size_t COMMANDS_DATA_SIZE = ARRAY_SIZE(COMMANDS_DATA);
