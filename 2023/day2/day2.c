#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int nbBlue = 14;
    int nbRed = 12;
    int nbGreen = 13;

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
        int valid = 0;
        while (line[i] != '\n' && line[i] != '\0') {
            i++;
            int nbR = 0;
            int nbG = 0;
            int nbB = 0;
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
                        nbG += tmp;
                        break;
                    case 'r':
                        i += 3;
                        nbR += tmp;
                        break;
                    case 'b':
                        i += 4;
                        nbB += tmp;
                        break;
                    default:
                        break;
                }
                if (line[i] == ',') {
                    i++;
                }
            }
            if (nbR > nbRed || nbG > nbGreen || nbB > nbBlue) {
                valid = 1;
                break;
            }
        }
        if (valid == 0) {
            acc += nbLine;
        }
        nbLine++;
    }
    fclose(file);
    free(line);
    printf("%ld\n",acc);
}
