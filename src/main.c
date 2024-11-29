
#include "URI.h"
#include "common.h"
// #include "server.h"
#include "request.h"
#include <mongoc/mongoc.h>

int main(void)
{
    // MONGO STUFF

    const char *uri_string = MONGO_URI;

    mongoc_uri_t *uri;
    mongoc_client_t *client;
    bson_t *command, reply;
    bson_error_t error;

    char *str;
    bool retval;

    /*
     * Initialize libmongoc
     */
    mongoc_init();

    // Create a MongoDB URI object from the string;
    uri = mongoc_uri_new_with_error(uri_string, &error);
    if (!uri)
    {
        fprintf(stderr,
                "failed to parse URI: %s\n"
                "error message:       %s\n",
                uri_string, error.message);

        return EXIT_FAILURE;
    }

    /*
     * Create a new client instance, here we use the uri we just built
     */
    client = mongoc_client_new_from_uri(uri);
    if (!client)
    {
        return EXIT_FAILURE;
    }

    // we already ahve the appname in the mongo uri
    // mongoc_client_set_appname(client, "my-mongo-connection");

    command = BCON_NEW("ping", BCON_INT32(1));

    // we run above command on our DB, using the client. We get reply and error
    // (if any)
    retval = mongoc_client_command_simple(client, "admin", command, NULL, &reply,
                                          &error);

    if (!retval)
    {
        fprintf(stderr, "%s\n", error.message);
    }

    // str = bson_as_json(&reply, NULL);
    str = bson_as_canonical_extended_json(&reply, NULL);

    printf("JSON response is: %s\n", str);

    /*
     * Clean up memory
     */
    bson_destroy(&reply);
    bson_destroy(command);
    bson_free(str);

    /*
     * Release our handles and clean up libmongoc
     */
    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    // int server_fd = 0;
    // struct sockaddr_in server_addr;
    // server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // if (server_fd < 0)
    // {
    //     perror("Socket failed");
    //     exit(EXIT_FAILURE);
    // }

    // server_addr.sin_familyhich mongo-c-driver    = AF_INET;
    // server_addr.sin_addr.s_addr = INADDR_ANY;
    // server_addr.sin_port = htons(PORT);

    // if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    // {
    //     perror("Bind failed");
    //     exit(EXIT_FAILURE);
    // }

    // if (listen(server_fd, 10) < 0)
    // {
    //     perror("Listen failed");
    //     exit(EXIT_FAILURE);
    // }

    // printf("Server is listening on port: \t%d\n", PORT);
    // while (1)
    // {
    //     struct sockaddr_in client_addr;
    //     socklen_t client_addr_len = sizeof(client_addr);

    //     int *client_fd = malloc(sizeof(int));
    //     *client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

    //     if (*client_fd < 0)
    //     {
    //         perror("Failed to accept");
    //         continue;
    //     }

    //     pthread_t thread_id;
    //     pthread_create(&thread_id, NULL, handle_request, (void *)client_fd);
    //     pthread_detach(thread_id);

    //     // free(client_fd);
    //     // client_fd = NULL;
    // }

    exit(EXIT_SUCCESS);
}
