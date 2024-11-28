// #include <stdio.h>
// #include <sys/socket.h> // Core socket API
// #include <netinet/in.h> // sockaddr_in and IP-related constants
// #include <arpa/inet.h>  // IP address conversion utilities (e.g., inet_pton)
// #include <unistd.h>
// #include <stdlib.h>
// #include <string.h>
// #include "server.h"

// int create_server_socket(int port)
// {
//     int server_fd;

//     struct sockaddr_in server_addr;

//     server_fd = socket(AF_INET, SOCK_STREAM, 0);
//     if (server_fd < 0)
//     {
//         perror("Socket creation failed");
//         exit(EXIT_FAILURE);
//     }
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     server_addr.sin_port = htons(port);

//     if (
//         bind(server_fd,
//              (struct sockaddr *)&server_addr,
//              sizeof(server_addr)) < 0)
//     {
//         perror("Bind failed");
//         close(server_fd);
//         exit(EXIT_FAILURE);
//     }

//     if (listen(server_fd, 10) < 0)
//     {
//         perror("Listening failed");
//         close(server_fd);
//         exit(EXIT_FAILURE);
//     }

//     printf("Server is listening on port: %d\t ", port);
//     return server_fd;
// }
