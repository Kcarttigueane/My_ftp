/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** circular_buffet.c
*/

#include "server.h"

void cb_init(circular_buffer* cb)
{
    cb->read_index = 0;
    cb->write_index = 0;
}

bool is_cb_full(circular_buffer* cb)
{
    return ((cb->write_index + 1) >= BUFFER_SIZE);
}

void cb_push(circular_buffer* cb, char* input_command)
{
    for (size_t i = 0; i < strlen(input_command); i++) {
        if (is_cb_full(cb))
            cb->write_index = 0;
        cb->buffer[cb->write_index] = input_command[i];
        cb->write_index += 1;
    }
}

int find_CRLF_index(circular_buffer* cb)
{
    size_t isCRLF = 0;

    for (size_t i = cb->read_index; i < BUFFER_SIZE; i++) {
        if ((i + 1) >= BUFFER_SIZE) {
            i = 0;
            continue;
        }
        if (cb->buffer[i] == '\r') {
            isCRLF = 1;
            continue;
        }
        if (isCRLF && cb->buffer[i] == '\n') {
            isCRLF = 2;
            return i;
        }
        if (i == cb->read_index) {
            return FAILURE;
        }
    }
    return FAILURE;
}

char** cb_pop_command(circular_buffer* cb)
{
    int CRLF_index = find_CRLF_index(cb);

    int nb_char_to_copy = CRLF_index - cb->read_index;

    if (CRLF_index == FAILURE)
        return NULL;

    char* command = malloc(sizeof(char) * (nb_char_to_copy + 1));

    for (size_t i = 0; i < (size_t)nb_char_to_copy; i++) {
        if (cb->read_index >= BUFFER_SIZE)
            cb->read_index = 0;
        command[i] = cb->buffer[cb->read_index++];
    }
    command[nb_char_to_copy] = '\0';

    char** command_array = split_str(command, " ");

    if (!command_array)
        return NULL;

    return command_array;
};
