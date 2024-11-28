#include "common.h"
#include "utils.h"
#include "request.h"
#include "response.h"

void *handle_request(void *arg)
{
    int client_fd = *((int *)arg);

    char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

    ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);

    if (bytes_received <= 0)
    {
        close(client_fd);
        free(arg);
        free(buffer);
        return NULL;
    }

    regex_t regex;
    regcomp(&regex, "GET /([^ ]*) HTTP/1", REG_EXTENDED);
    regmatch_t matches[2];

    if (regexec(&regex, buffer, 2, matches, 0) == 0)
    {
        buffer[matches[1].rm_eo] = '\0';
        const char *url_encoded_file_name = buffer + matches[1].rm_so;
        char *file_name = url_decode(url_encoded_file_name);

        char file_ext[32];
        strcpy(file_ext, get_file_extension(file_name));
        char *response = (char *)malloc(BUFFER_SIZE * 2 * sizeof(char));
        size_t response_len;

        if (strlen(file_name) == 0)
        {
            build_http_response("index.html", "html", response, &response_len);
        }
        else
        {
            build_http_response(file_name, file_ext, response, &response_len);
        }

        send(client_fd, response, response_len, 0);

        free(file_name);
        free(response);
        file_name = NULL;
        response = NULL;
    }

    regfree(&regex);

    close(client_fd);
    free(arg);
    free(buffer);
    return NULL;
};