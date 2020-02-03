#include "../includes/server.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void error(int32_t new_socket, char *reason)
{
    char *headers;

    printf("%s\n",reason);
    headers = "HTTP/1.1 404 Not Found\nContent-Type: application/json\n\n";
    pthread_mutex_unlock(&lock);
    ft_putstr_fd(ft_strjoin(headers, reason), new_socket);
}

static void response(int32_t new_socket)
{
    char buffer[1024] = {0};
    char *headers;

    read(new_socket, buffer,1024);

    t_request *req = parse_request(buffer);
    if (req)
    {
        if (req->method & POST)
        {
            if (ft_strcmp(req->url, "/hashes") == 0)
            {
                if (ft_strlen(req->body) >= 1)
                {
                    headers = "HTTP/1.1 200 OK\nContent-Type: application/json\n\n";
                    pthread_mutex_unlock(&lock);
                    ft_putstr_fd(ft_strjoin(headers, hashes(req->body)), new_socket);
                }
                else
                    error(new_socket, "Error. Can not parse the request");
            }
            else
                error(new_socket, "Page not found");
        }
    }
    else
        error(new_socket, "Error. Can not parse the request");
    free_request(req);
}


static void *socket_thread(void *arg)
{
    int32_t new_socket = *((int *)arg);

    pthread_mutex_lock(&lock);

    response(new_socket);

    close(new_socket);
    pthread_exit(NULL);
}

int main()
{
    int32_t             server_fd;
    int32_t             new_socket;
    struct sockaddr_in  address;
    int32_t             addr_len;
    int8_t              running = 1;
    int32_t             i;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    ft_memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1000) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1000) == 0)
        printf("Listening\n");
    else
        printf("Error\n");
    pthread_t tid[1024];
    i = -1;
    while (running)
    {
        ++i;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len)) < 0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        if (pthread_create(&tid[i], NULL, socket_thread, &new_socket) != 0)
            printf("Failed to create thread\n");
        if (i >= 1000)
        {
            i = 0;
            while (i < 1000)
                pthread_join(tid[i++], NULL);
        }
    }
    return 0;
}