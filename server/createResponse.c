#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char const* const fileName = "studentlist"; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];
    char stdnr[10];
    char name[50];
    char filename[50];
    char response[1000];

    while (fgets(line, sizeof(line), file)) {
        memset(stdnr, 0, 10);
        memset(name, 0, 50);
        memset(filename, 0, 50);
        strcpy(filename, "res");
        strncpy(stdnr, line, 6);
        strcat(filename, stdnr);
        strcpy(name, strchr(line, ' ') + 1);
        *(strchr(name, '\n')) = '\0';
        printf("%s - %s", filename, name);
        FILE* respFile = fopen(filename, "w");
        fputs("Hei, ", respFile);
        fputs(name, respFile);
        fputs("!\n", respFile);
        fputs("Naa skal du gjoere det samme som i den foerste oppgaven, ", respFile);
        fputs("men i et annet språk og/eller OS. Du skal også implementere ", respFile);
        fputs("3 nye meldinger med ID 0x03, 0x04 og 0x05. 0x03 er 'PING', ", respFile);
        fputs("og skal besvares med 0x04 'PONG'. Dette skal klienten gjoere ", respFile);
        fputs("helt til den faar en 0x05 'QUIT' melding, og da skal klienten ", respFile);
        fputs("koble fra serveren. Alle 3 meldinger har datastoerrelse 0. ", respFile);
        fputs("Oppgaven leveres som en rapport paa samme maatte som forrige gang.\n", respFile);
        fclose(respFile);
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

    return 0;    
}