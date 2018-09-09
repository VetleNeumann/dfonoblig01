#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(char* msg)
{
    perror(msg);
    exit(1);
}

void handleClient(int newsockfd)
{
    char buffer[1024];
    int n;

    bzero(buffer, 1024);
    n = read(newsockfd, buffer, 1023);
    if (n < 0)
        error("ERROR reading from socket");

    if (n == 6) {
        FILE* handle = fopen(buffer, "r");
        if (handle == NULL) {
            char* response = "Ugyldig studentnummer";
            n = write(newsockfd, response, strlen(response));
        }
        else {
            bzero(buffer, 1024);
            int ch, idx = 0;
            while ((ch = fgetc(handle)) != EOF) {
                buffer[idx++] = ch;
            }
            n = write(newsockfd, buffer, idx) - 1;
        }
    }
    else {
        char* errorMessage = "Ukjent kommando";
        n = write(newsockfd, errorMessage, strlen(errorMessage));
        if (n < 0)
            error("ERROR writing to socket");
    }
}