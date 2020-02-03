#include "../includes/server.h"

static void ft_form_hash(char **result, unsigned char hash)
{
    size_t  size;
    char    *buf;
    char    *temp;

    size = snprintf(NULL, 0, "%.2x", hash);
    buf = ft_strnew(size);
    snprintf(buf, size + 1, "%.2x", hash);
    temp = ft_strdup(*result);
    ft_memdel((void *)result);
    *result = ft_strjoin(temp, buf);
    ft_memdel((void **)&temp);
    ft_memdel((void **)&buf);
}

static void ft_form_result(char **result, uint8_t algo)
{
    char *temp_res;
    char *temp;

    if (algo & SHA512)
    {
        temp = ft_strdup("{\n \"sha512\": \"");
        temp_res = ft_strdup(*result);
        ft_memdel((void *)result);
        *result = ft_strjoin(temp, temp_res);
        ft_memdel((void **)&temp);
        ft_memdel((void **)&temp_res);
    }
    else if (algo & GOST)
    {
        temp = ft_strdup("\",\n \"gost\": \"");
        temp_res = ft_strdup(*result);
        ft_memdel((void *)result);
        *result = ft_strjoin(temp, temp_res);
        ft_memdel((void **)&temp);
        ft_memdel((void **)&temp_res);
    }
    else if (algo & FINAL)
    {
        temp = ft_strdup("\"\n}");
        temp_res = ft_strdup(*result);
        ft_memdel((void *)result);
        *result = ft_strjoin(temp_res, temp);
        ft_memdel((void **)&temp);
        ft_memdel((void **)&temp_res);
    }
}

static char *ft_sha512(char *data)
{
    uint32_t        i;
    MHASH           td;
    unsigned char   hash[mhash_get_block_size(MHASH_SHA512)];
    char            *result;

    td = mhash_init(MHASH_SHA512);
    result = ft_strnew(1);

    if (td == MHASH_FAILED)
        exit(1);

    mhash(td, data, strlen(data));
    mhash_deinit(td, hash);

    for (i = 0; i < mhash_get_block_size(MHASH_SHA512); i++)
        ft_form_hash(&result, hash[i]);

    ft_form_result(&result, SHA512);
    return (result);
}

static char *ft_gost(char *data)
{
    uint32_t        i;
    MHASH           td;
    unsigned char   hash[mhash_get_block_size(MHASH_GOST)];
    char            *result;

    td = mhash_init(MHASH_GOST);
    result = ft_strnew(1);

    if (td == MHASH_FAILED)
        exit(1);

    mhash(td, data, strlen(data));
    mhash_deinit(td, hash);

    for (i = 0; i < mhash_get_block_size(MHASH_GOST); i++)
        ft_form_hash(&result, hash[i]);

    ft_form_result(&result, GOST);
    return (result);
}

char        *hashes(char *data)
{
    char *result;
    char *sha512;
    char *gost;

    sha512 = ft_sha512(data);
    gost = ft_gost(data);

    result = ft_strjoin(sha512, gost);
    
    ft_form_result(&result, FINAL);
    return (result);
}

// curl -X POST -H 'Content-type: application/json' --data '{"data":"abc"}' 'localhost:8000/hashes'