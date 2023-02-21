/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** circular_buffer.h
*/

#if !defined(CIRCULAR_BUFFER_H)
    #define CIRCULAR_BUFFER_H

    #include "server.h"

    typedef struct cb {
        char buffer[BUFFER_SIZE];
        size_t read_index;
        size_t write_index;
    } circular_buffer;

// ! Circular Buffer:

void cb_init(circular_buffer* cb);
bool is_cb_full(circular_buffer* cb);

void cb_push(circular_buffer* cb, char* input_command);
char** cb_pop_command(circular_buffer* cb);
int find_CRLF_index(circular_buffer* cb);

#endif // CIRCULAR_BUFFER_H
