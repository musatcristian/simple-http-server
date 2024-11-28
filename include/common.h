#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 104857600
#define INDEX_HTML "HTTP/1.1 200 OK\r\n"         \
                   "Content-Type: text/html\r\n" \
                   "Content-Length: 45\r\n"      \
                   "\r\n"                        \
                   "<html><body><h1>Welcome!</h1></body></html>"

#endif