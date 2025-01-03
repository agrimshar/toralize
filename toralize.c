/* toralize.c */
#include "toralize.h"

ProxyRequest *request(const char *dstip, const int dstport)
{
    ProxyRequest *req = (ProxyRequest *)malloc(REQUESTSIZE);
    if (req == NULL)
    {
        perror("malloc");
        return NULL;
    }

    req->VN = 4;
    req->CD = 1;
    req->DSTPORT = htons(dstport);
    req->DSTIP = inet_addr(dstip);
    strncpy(req->USERID, USERNAME, 8);

    return req;
}

int main(int argc, char *argv[]) 
{
    char *host;
    int port, s;
    struct sockaddr_in sock;
    ProxyRequest *req;
    ProxyResponse *res;
    char buf[RESPONSESIZE];
    int success;
    char temp[512];

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);

        return -1;
    }

    host = argv[1];
    port = atoi(argv[2]);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0)
    {
        perror("socket");
        return -1;
    }

    sock.sin_family = AF_INET;
    sock.sin_port = htons(PROXYPORT);
    sock.sin_addr.s_addr = inet_addr(PROXY);

    if (connect(s, (struct sockaddr *)&sock, sizeof(sock)))
    {
    
        perror("connect");
        return -1;
    }

    printf("Connected to %s:%d\n", PROXY, PROXYPORT);

    req = request(host, port);
    if (req == NULL)
    {
        perror("request");
        return -1;
    }

    if (write(s, req, REQUESTSIZE) < 0)
    {
        perror("write");
        return -1;
    }

    memset(buf, 0, RESPONSESIZE);

    if(read(s, buf, RESPONSESIZE) < 1)
    {
        perror("read");
        free(req);
        close(s);
        return -1;
    }

    res = (ProxyResponse *)buf;
    success = (res->CD == 90);

    if (!success)
    {
        fprintf(stderr, "Connection failed: %d\n", res->CD);
        free(req);
        close(s);
        return -1;
    }

    printf("Connection successful through the proxy %s:%d\n", host, port);

    memset(temp, 0, 512);
    snprintf(temp, 511, "HEAD / HTTP/1.0\r\n"
                         "Host: google.com\r\n"
                         "\r\n");
    
    write(s, temp, strlen(temp));

    memset(temp, 0, 512);

    read(s, temp, 511);
    printf("'%s'\n", temp);
    
    close(s);
    free(req);

    return 0;
}