#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

#define HOST "www.googleapis.com"
#define PORT "443"

/* https://developers.google.com/calendar/api/v3/reference/events/list */
#define CALENDAR_ID ""
#define QUERY_TIME_MIN "timeMin=2022-10-23T00:00:00Z"
#define QUERY_TIME_MAX "timeMax=2022-10-23T23:59:59Z"
#define PATH "/calendar/v3/calendars/" CALENDAR_ID "/events?" \
        QUERY_TIME_MIN "&" QUERY_TIME_MAX

/* https://developers.google.com/identity/protocols/oauth2/service-account */
#define TOKEN ""

int main() {
    int size;
    char buf[1024];
    BIO* bio;
    /* SSL* ssl; */
    SSL_CTX* ctx;
    char* write_buf = "GET " PATH " HTTP/1.1\n"
                      "Host: " HOST "\n"
                      "Authorization: Bearer " TOKEN "\r\n"
                      "Connection: close\n"
                      "\n";

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
