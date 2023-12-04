#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 0;
    int nbCopies[187] = {0};

    for (int x = 0; x < 187; x++) {
        nbCopies[x] = 1;
    }

    while ((nread = getline(&line, &len, file)) != -1) {
        int array[10] = {0};

        int i = 0;
        int point = 0;
        while (line[i] != ':') {
            i++;
        }
        i++;
        int j = 0;
        while (line[i] != '|') {
            while (line[i] == ' ') {
                i++;
            }
            while (isdigit(line[i])) {
                array[j] = array[j] * 10 + line[i++] - '0';        
            }
            j++;
        }
        i++;
        int count = 0;
        while (line[i] != '\n' && line[i] != '\0') {
            while (line[i] == ' ') {
                i++;
            }
            int num = 0;
            while (isdigit(line[i])) {
                num = num * 10 + line[i++] - '0';
            }
            for (int k = 0; k < 10; k++) {
                if (array[k] == num) {
                    nbCopies[nbLine + ++count] += nbCopies[nbLine];
                }
            }
        }

        acc += nbCopies[nbLine++];
    }

    printf("The result is %ld\n", acc);
}

