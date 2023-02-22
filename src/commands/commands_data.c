/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** commands_data.c
*/

#include "../../include/server.h"

const command_t COMMANDS_DATA[] = {
    {"HELP", "List available commands\r\n"},
    {"NOOP", "Do nothing\r\n"},
    {"USER", "Specify user for authentication\r\n"},
    {"PASS", "Specify password for authentication\r\n"},
    {"CWD", "Change working directory\r\n"},
    {"CDUP", "Change working directory to parent directory\r\n"},
    {"QUIT", "Disconnection\r\n"},
    {"DELE", "Delete file on the server\r\n"},
    {"PWD", "Print working directory\r\n"},
    {"PASV", "Enable \"passive\" mode for data transfer\r\n"},
    {"PORT", "Enable \"active\" mode for data transfer\r\n"},
    {"RETR", "Download file from the server to the client\r\n"},
    {"STOR", "Upload file from the client to the server\r\n"},
    {"LIST", "List files in the current working directory\r\n"},
};
