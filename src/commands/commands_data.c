/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** commands_data.c
*/

#include "../../include/server.h"

const command_t COMMANDS_DATA[] = {
    {"HELP", "List available commands"},
    {"NOOP", "Do nothing"},
    {"USER", "Specify user for authentication"},
    {"PASS", "Specify password for authentication"},
    {"CWD", "Change working directory"},
    {"CDUP", "Change working directory to parent directory"},
    {"QUIT", "Disconnection"},
    {"DELE", "Delete file on the server"},
    {"PWD", "Print working directory"},
    {"PASV", "Enable \"passive\" mode for data transfer"},
    {"PORT", "Enable \"active\" mode for data transfer"},
    {"RETR", "Download file from the server to the client"},
    {"STOR", "Upload file from the client to the server"},
    {"LIST", "List files in the current working directory"},
};
