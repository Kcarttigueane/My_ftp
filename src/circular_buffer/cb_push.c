/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** cb_push.c
*/

#include "../../include/server.h"

void cb_push(circular_buffer* cb, char* input_command)
{
    for (size_t i = 0; input_command[i] != '\0'; i++) {
        if (is_cb_full(cb))
            cb->write_index = 0;
        cb->buffer[cb->write_index] = input_command[i];
        cb->write_index++;
    }
}
