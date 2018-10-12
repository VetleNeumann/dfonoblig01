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

    char errorByte = 0x00;
    if (buffer[0] != 0x01) {
      errorByte += 0x01;
    }
    short messageLength = (((short)buffer[1]) << 8) | (0x00ff & buffer[2]);
    if (messageLength != n - 3) {
      errorByte += 0x02;
    }
    if (buffer[3] != n - 4) {
      errorByte += 0x04;
    }
    if (n == 10) {
        char filename[100] = "res";
        strcat(filename, buffer + 4);
        printf("opening %s\n", filename);
        FILE* handle = fopen(filename, "r");
        if (handle == NULL) {
            errorByte += 0x08;
        }
        else if (errorByte == 0) {
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
            return;
        }
    }
    else {
        errorByte += 0x10;
    }

    char response[512] = {0};
    if ((errorByte & 0x01) > 0) {
      strcat(response, "\nUkjent kommando ID");
    }
    if ((errorByte & 0x02) > 0) {
      strcat(response, "\nAngitt datalengde matcher ikke datalengden");
    }
    if ((errorByte & 0x04) > 0) {
      strcat(response, "\nStudentnr størrelse matcher ikke angitt studentnr");
    }
    if ((errorByte & 0x08) > 0) {
      strcat(response, "\nUgyldig studentnummer");
    }
    if ((errorByte & 0x10) > 0) {
      strcat(response, "\nUforventet meldingslengde");
    }
    strcat(response, "\nServeren mottok: \n");
    for (int i = 0; i < 4; i++)
      buffer[i] += 48;
    strcat(response, buffer);

    n = write(newsockfd, response+1, 511);
    if (n < 0)
      error("ERROR writing to socket");
}
