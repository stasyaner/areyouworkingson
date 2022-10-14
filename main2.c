#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#define APIKEY "YOUR_API_KEY"
#define HOST "example.com"
#define PORT "443"

int main() {
    int size;
    char buf[1024];
    BIO* bio;
    /* SSL* ssl; */
    SSL_CTX* ctx;
    char* write_buf = "POST / HTTP/1.1\r\n"
                      "Host: " HOST "\r\n"
                      /* "Authorization: Basic " APIKEY "\r\n" */
                      "Connection: close\r\n"
                      "\r\n";

    SSL_library_init();

    ctx = SSL_CTX_new(SSLv23_client_method());

    if (ctx == NULL)
    {
        printf("Ctx is null\n");
    }

    bio = BIO_new_ssl_connect(ctx);


    BIO_set_conn_hostname(bio, HOST ":" PORT);

    if(BIO_do_connect(bio) <= 0)
    {
        printf("Failed connection\n");
        return 1;
    }
    else
    {
        printf("Connected\n");
    }

    if(BIO_write(bio, write_buf, strlen(write_buf)) <= 0)
    {
        if(!BIO_should_retry(bio))
        {
            /* Not worth implementing, but worth knowing. */
        }

        printf("Failed write\n");
    }

    for(;;)
    {
        size = BIO_read(bio, buf, 1023);

        if(size <= 0)
        {
            break;
        }

        buf[size] = 0;

        printf("%s", buf);
    }

    BIO_free_all(bio);
    SSL_CTX_free(ctx);

    return 0;
}
