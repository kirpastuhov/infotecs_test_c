#include "../includes/server.h"

// int main(void)
// {
//     int32_t             server_fd;
//     int32_t             new_socket;
//     char                *headers;
//     struct sockaddr_in  address;
//     int32_t             addr_len;
//     int8_t              running;

//     addr_len = sizeof(address);
    
//     // char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
//     running =1;
//     // Creating socker file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//     {
//         perror("In socket");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     ft_memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
//     {
//         perror("In bind");
//         exit(EXIT_FAILURE);
//     }
//     if (listen(server_fd, 1000) < 0)
//     {
//         perror("In listen");
//         exit(EXIT_FAILURE);
//     }
//     while (running)
//     {
//         printf("\n+++++++ Waiting for new connection ++++++++\n\n");
//         if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len)) < 0)
//         {
//             perror("In accept");
//             exit(EXIT_FAILURE);
//         }
//         char buffer[1024] = {0};
//         read(new_socket, buffer, 1024);
        
//         t_request *req = parse_request(buffer);
//         if (req) 
//         {
//             // printf("Method: %d\n", req->method);
//             // printf("Request-URI: %s\n", req->url);
//             // printf("HTTP-Version: %s\n", req->version);
//             // puts("Headers:");
//             // t_header *h;
//             // for (h = req->headers; h; h = h->next)
//             // {
//             //     printf("%32s: %s\n", h->name, h->value);
//             // }
//             // puts("message-body:");
//             // puts(req->body);
//             if (req->method & POST)
//             {
//                 if (ft_strcmp(req->url, "/hashes") == 0)
//                 { 
//                     // printf("URL = %s\n", req->url);
//                     if (ft_strlen(req->body) >= 1)
//                     {
//                         headers = "HTTP/1.1 200 OK\nContent-Type: application/json\n\n";
//                         ft_putstr_fd(ft_strjoin(headers, hashes(req->body)), new_socket);
//                         printf("Success\n");
//                     }
//                     else
//                     {
//                         printf("Failure No body\n");
//                         // break;
//                     }
                    
//                 }
//                 else
//                 {
//                     // printf("URL = %s\n", req->url);
//                     // printf("URL = %d\n", ft_strcmp(req->url, "/hashes"));
//                     printf("Failure\n");
//                     headers = "HTTP/1.1 404 Not Found\nContent-Type: application/json\n\nNot Found";
//                     ft_putstr_fd(headers, new_socket);
//                 }
                
//             }
//         }
//         else
//         {
//             headers = "HTTP/1.1 404 Not Found\nContent-Type: application/json\n\nNot Found";
//             ft_putstr_fd(headers, new_socket);
//         }
        
//         free_request(req);

//         // printf("------------------Hello message sent-------------------\n");
//         close(new_socket);
//         // curl -d '{"data":"hash"}' 'localhost:8000/dick' 
//     }
//     return (0);
// }
