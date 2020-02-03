#include "../includes/server.h"

t_request *parse_request(const char *raw) 
{
    t_request *req = NULL;
    req = ft_memalloc(sizeof(t_request));
    if (!req) 
        return NULL;

                                          // Method
    size_t method_len = strcspn(raw, " ");
    if (ft_memcmp(raw, "GET", strlen("GET")) == 0) 
        req->method |= GET;
    else if (ft_memcmp(raw, "POST", strlen("POST")) == 0)
        req->method |= POST;
    else
        req->method |= UNSUPPORTED;
    raw += method_len + 1;                // move past <SP>

                                          // Request-URI
    size_t url_len = strcspn(raw, " ");
    req->url = ft_strndup(raw, url_len);
    if (!req->url)
    {
        free_request(req);
        return NULL;
    }
    raw += url_len + 1;                   // move past <SP>

                                          // HTTP-Version
    size_t version_len = strcspn(raw, "\r\n");
    req->version = ft_strndup(raw, version_len);
    if (!req->version)
    {
        free_request(req);
        return NULL;
    }
    raw += version_len + 2;               // move past <CR><LF>

    t_header *header = NULL;
    t_header *last = NULL;
    while (raw[0] != '\r' || raw[1] != '\n')
    {
        last = header;
        header = ft_memalloc(sizeof(t_header));
        if (!header)
        {
            free_request(req);
            return NULL;
        }

        size_t name_len = strcspn(raw, ":");
        header->name = ft_strndup(raw, name_len);
        if (!header->name)
        {
            free_request(req);
            return NULL;
        }
        raw += name_len + 1;              // move past :
        while (*raw == ' ')
            raw++;

        size_t value_len = strcspn(raw, "\r\n");
        header->value = ft_strndup(raw, value_len);
        if (!header->value)
        {
            free_request(req);
            return NULL;
        }
        raw += value_len + 2;              // move past <CR><LF>

        header->next = last;
    }
    req->headers = header;
    raw += 2;                             // move past <CR><LF>

    size_t data_len = strcspn(raw, ":");   
    raw += data_len + 2;                  // move past {"data":"
    size_t hash_end = strcspn(raw, "\""); // seek end of hash
    req->body = ft_strndup(raw, hash_end);
    if (!req->body)
    {
        free_request(req);
        return NULL;
    }
    return req;
}


void free_header(t_header *h)
{
    if (h)
    {
        free(h->name);
        free(h->value);
        free_header(h->next);
        free(h);
    }
}

void free_request(t_request *req) {
    free(req->url);
    free(req->version);
    free_header(req->headers);
    free(req->body);
    free(req);
}