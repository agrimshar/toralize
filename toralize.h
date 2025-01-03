/* toralize.h */
#ifndef TORALIZE_H
#define TORALIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PROXY "127.0.0.1"
#define PROXYPORT 9050

typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;

struct proxy_request {
    int8 VN;
    int8 CD;
    int16 DSTPORT;
    int32 DSTIP;
    int8 USERID[8];
};
typedef struct proxy_request ProxyRequest;

/*
                +----+----+----+----+----+----+----+----+----+----+....+----+
                | VN | CD | DSTPORT |      DSTIP        | USERID       |NULL|
                +----+----+----+----+----+----+----+----+----+----+....+----+
 # of bytes:	   1    1      2              4           variable       1
*/

struct proxy_response {
    int8 VN;
    int8 CD;
    int16 DSTPORT;
    int32 DSTIP;
};
typedef struct proxy_response ProxyResponse;

/*
                +----+----+----+----+----+----+----+----+
                | VN | CD | DSTPORT |      DSTIP        |
                +----+----+----+----+----+----+----+----+
 # of bytes:	   1    1      2              4
*/

#endif