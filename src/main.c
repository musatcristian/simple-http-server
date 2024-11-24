#include "common.h"
#include "server.h"

int main(void)
{
    int port = 8080;
    int server_fd = create_server_socket(port);
    if (server_fd < 0)
    {
        fprintf(stderr, "Socket creation failed");
        return 1;
    }


    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    printf("Server is listening on port: %d\n", port);

    while (1) {
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Client connected!\n");

        // Send a welcome message to the client
        char *message = "Hello from server!\n";
        send(client_fd, message, strlen(message), 0);

        // Close the client socket
        close(client_fd);
        printf("Client disconnected.\n");
    }

    close(server_fd);
    exit(EXIT_SUCCESS);
}
