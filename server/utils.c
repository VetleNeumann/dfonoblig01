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

    if (n == 10) {
        if (buffer[0] != 0x01) {
            char* response = "Ugyldig kommando";
            n = write(newsockfd, response, strlen(response));
            return;
        }
        char filename[100] = "res";
        strcat(filename, buffer + 4);
        printf("opening %s\n", filename);
        FILE* handle = fopen(filename, "r");
        if (handle == NULL) {
            char* response = "Ugyldig studentnummer";
            n = write(newsockfd, response, strlen(response));
        }
        else {
            bzero(buffer, 1024);
            buffer[0] = 0x2;
            int ch, idx = 5;
            while ((ch = fgetc(handle)) != EOF) {
                buffer[idx++] = ch;
            }
            unsigned short messageSize = htons(idx - 3);
            unsigned short textSize = htons(idx - 5);
            memcpy(buffer + 1, &messageSize, 2);
            memcpy(buffer + 3, &textSize, 2);
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