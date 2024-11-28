#include "common.h"
// #include "server.h"
#include "request.h"

int main(void)
{
    int server_fd = 0;
    struct sockaddr_in server_addr;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0)
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port: \t%d\n", PORT);
    while (1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

        if (*client_fd < 0)
        {
            perror("Failed to accept");
            continue;
        }

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_request, (void *)client_fd);
        pthread_detach(thread_id);

        // free(client_fd);
        // client_fd = NULL;
    }

    exit(EXIT_SUCCESS);
}
