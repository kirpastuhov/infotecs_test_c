#ifndef SERVER_H
# define SERVER_H

# include "../libft/libft.h"
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/socket.h>
# include <unistd.h>
# include <netinet/in.h>
# include <mhash.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/types.h>


#define PORT 8000


# define POST 1
# define UNSUPPORTED 2
# define GET 4

# define SHA512 1
# define GOST 2
# define FINAL 4


typedef struct      s_header 
{
    char            *name;
    char            *value;
    struct s_header *next;
}                   t_header;

typedef struct      s_request 
{
    uint8_t         method : 5;
    char            *url;
    char            *version;
    t_header        *headers;
    char            *body;
}                   t_request;


t_request           *parse_request(const char *raw);
void                free_header(t_header *h);
void                free_request(t_request *req);
char                *hashes(char *data);
char                *ft_itoa_base(uint64_t nbr, int base);

#endif