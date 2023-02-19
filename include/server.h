/*
** EPITECH PROJECT, 2023
** STEP-1
** File description:
** main.c
*/

#if !defined(SERVER_H)
    #define SERVER_H

    #include <sys/select.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <sys/un.h>
    #include <sys/stat.h>

    #include <netinet/in.h>

    #include <arpa/inet.h>
    #include <netdb.h>

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "unistd.h"

    #include <errno.h>

    #include <signal.h>
    #include <stdbool.h>


    // ! Project header files:

    #include "lib.h"
    #include "reply_codes.h"
    #include "utils.h"
    #include "commands.h"

    // ! Error Status Codes :

    #define ERROR 84
    #define SUCCESS 0
    #define FAILURE -1

    #define QUEUE_LEN 5
    #define BUFFER_SIZE 1024

    #define ANONYMOUS_USERNAME "Anonymous"
    #define ANONYMOUS_PASSWORD ""

    #define SERVER_USAGE \
        "USAGE: ./myftp port path\n\
    \tport is the port number on which the server socket listens\n\
    \tpath is the path to the home directory for the Anonymous user\n"

    // ! CoMMANDSs functions:

    #define handle_error(msg) \
        do {                  \
            perror(msg);      \
            exit(ERROR);      \
        } while (0)

    // ! Structures:

    typedef struct server_data {
        int PORT;
        int server_socket_fd;
        struct sockaddr_in server_address;
        int fd_max, fd_num, read_input_len;
        struct timeval timeout;
        fd_set fds, copy_fds;
        char buffer[BUFFER_SIZE];
        size_t nb_clients;
    } server_data_t;

    typedef struct client {
        int client_socked_fd;
        struct sockaddr_in client_address;
        char username[BUFFER_SIZE];
        char password[BUFFER_SIZE];
        bool is_logged;
        char current_path[BUFFER_SIZE];
        socklen_t client_len;
    } client_t;

    typedef struct {
        char buffer[BUFFER_SIZE];
        size_t read_index;
        size_t write_index;
    } circular_buffer;

    typedef struct command
    {
        char *name;
        char *description;
    } command_t;



    // ! Functions prototypes:

void init_server(server_data_t* server_data, char const* argv[]);
void create_socket(server_data_t* server_data);
void bind_socket(server_data_t* server_data);
void listen_socket(server_data_t* server_data);

void is_valid_path(const char* path);

// ! Circular Buffer:

void cb_init(circular_buffer* cb);
bool is_cb_full(circular_buffer* cb);

void cb_push(circular_buffer* cb, char* input_command);
char** cb_pop_command(circular_buffer* cb) ;int find_CRLF_index(
    circular_buffer* cb);

// FTP:

void parse_command(circular_buffer* cb, server_data_t* server_data, int i);
void myFTP_loop(server_data_t* server_data, client_t* clients);

void send_resp(int socket_fd, char* msg);

// ! Signal handlers:

void sigint_handler(int signal);
void sigterm_handler(int signal);

extern const command_t COMMANDS_DATA[];

#endif // SERVER_H

