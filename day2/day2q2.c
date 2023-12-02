#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;

    while ((nread = getline(&line, &len, file)) != -1) {
        int i = 0;
        while (line[i] != ':') {
            i++;
        }
        int nbR = 0;
        int nbG = 0;
        int nbB = 0;
        while (line[i] != '\n' && line[i] != '\0') {
            i++;
            int nbRtmp = 0;
            int nbGtmp = 0;
            int nbBtmp = 0;
            while (line[i] != ';' && line[i] != '\n') {
                i++;
                int tmp = 0;
                while (line[i] >= '0' && line[i]<= '9') {
                    tmp = tmp * 10 + line[i] - '0';
                    i++;
                }
                i++;
                switch (line[i]) {
                    case 'g':
                        i += 5;
                        nbGtmp += tmp;
                        break;
                    case 'r':
                        i += 3;
                        nbRtmp += tmp;
                        break;
                    case 'b':
                        i += 4;
                        nbBtmp += tmp;
                        break;
                    default:
                        break;
                }
                if (line[i] == ',') {
                    i++;
                }
            }
            nbR = (nbR > nbRtmp) ? nbR : nbRtmp;
            nbG = (nbG > nbGtmp) ? nbG : nbGtmp;
            nbB = (nbB > nbBtmp) ? nbB : nbBtmp;
        }
        acc += nbR * nbG * nbB;
        nbLine++;
    }
    fclose(file);
    free(line);
    printf("%ld\n",acc);
}
