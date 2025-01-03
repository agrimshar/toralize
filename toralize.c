/* toralize.c */
#include "toralize.h"

int main(int argc, char *argv[]) 
{
    char *host;
    int port;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);

        return -1;
    }
}