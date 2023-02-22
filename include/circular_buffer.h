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

// ! Init:

void cb_init(circular_buffer* cb);

// ! Check:

bool is_cb_full(circular_buffer* cb);

// ! Push:

void cb_push(circular_buffer* cb, char* input_command);

// ! Pop:

int find_crlf_index(circular_buffer* cb);
char* copy_chars(circular_buffer* cb, size_t nb_char_to_copy);
size_t get_nb_char_to_copy(circular_buffer* cb, int CRLF_index);
char** cb_pop_command(circular_buffer* cb);


#endif // CIRCULAR_BUFFER_H
