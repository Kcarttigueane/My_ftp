/*
** EPITECH PROJECT, 2022
** Repository-MyFTP
** File description:
** server.h
*/

#ifndef SERVER_H
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

    #include <dirent.h>

    #include <limits.h>
    #include <libgen.h>

    // ! Error Status Codes :

    #define ERROR 84
    #define SUCCESS 0
    #define FAILURE -1

    #define QUEUE_LEN 5
    #define BUFFER_SIZE 1024

    #define ANONYMOUS_USERNAME "Anonymous"
    #define ANONYMOUS_PASSWORD ""

    #define CRLF "\r\n"

    #define CARRIAGE_RETURN '\r'
    #define LINE_FEED '\n'

    #define PORT_ARGS_FORMAT "%[^,],%d,%d"

    #define SERVER_USAGE \
        "USAGE: ./myftp port path\n\
    \tport is the port number on which the server socket listens\n\
    \tpath is the path to the home directory for the Anonymous user\n"

    // ! COMMANDS functions:

    #define handle_error(msg) \
        do {                  \
            perror(msg);      \
            exit(ERROR);      \
        } while (0)


    // ! DATA MODE:

    typedef enum {
        NO_MODE,
        ACTIVE,
        PASSIVE
    } data_mode_t;

    // ! Structures:

    typedef struct server_data {
        int PORT;
        int server_socket_fd;
        struct sockaddr_in server_address, data_address;
        int fd_max, fd_num, read_input_len;
        struct timeval timeout;
        fd_set fds, copy_fds;
        size_t nb_clients;
        char* initial_path;

        data_mode_t data_mode;

        int data_socket_fd;
        socklen_t data_len;
    } server_data_t;

    typedef struct client {
        int client_socked_fd;
        struct sockaddr_in client_address;
        char username[BUFFER_SIZE];
        bool is_logged;
        char* current_path;
        socklen_t client_len;
    } client_t;

    typedef struct {
        int control_socket;
        server_data_t* server_data;
        char** input_command;
        client_t* clients;
    } list_args_t;

    typedef void (*command_func_t)(list_args_t* args);

    typedef struct command {
        char* name;
        char* description;
        command_func_t func;
    } command_t;

    // ! Project header files:

    #include "lib.h"
    #include "reply_codes.h"
    #include "utils.h"
    #include "commands.h"
    #include "circular_buffer.h"

    // ! Functions prototypes:

void init_server(server_data_t* server_data, char const* argv[]);
void create_socket(server_data_t* server_data);
void bind_socket(server_data_t* server_data);
void listen_socket(server_data_t* server_data);
int is_valid_path(const char* path);

bool check_directory_exists(const char* path);
bool check_directory(const char* path);
bool check_directory_permissions(const char* path);

    // ! Parsing commands:

void parse_command(circular_buffer* cb, server_data_t* server_data, int i,
client_t* clients);

    // ! FTP:

void my_ftp_loop(server_data_t* server_data, client_t* clients);

void send_resp(int socket_fd, char* msg);

void handle_new_client_connection(server_data_t* server_data,
client_t* clients);

void accept_new_client(server_data_t* server_data, client_t* clients);

bool is_logged(int control_socket, client_t* clients);

int create_temp_socket(server_data_t* server_data, client_t* clients);

FILE* open_file(char* file_name, int control_socket, char* message);

bool is_data_con_establish(int control_socket,
server_data_t* server_data);

bool is_directory_accessible(int control_socket, server_data_t *server_data,
char *new_path);

extern const command_t COMMANDS_DATA[];
extern const size_t COMMANDS_DATA_SIZE;

#endif // SERVER_H
