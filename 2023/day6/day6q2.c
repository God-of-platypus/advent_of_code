#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;

    int64_t time = 0;

    int64_t dist = 0;

    nread = getline(&line, &len, file);
    int i = 0;
    while (line[i] != '\n') {
        while(line[i] != ':') {
            i++;
        }
        i++;
        while(line[i] != '\n') {
            while (line[i] == ' ') {
                i++;
            }
            while (isdigit(line[i])) {
                time = time * 10 + line[i++] - '0';
            }
        }
    }
    nread = getline(&line, &len, file);
    i = 0;
    while (line[i] != '\n') {
        while(line[i] != ':') {
            i++;
        }
        i++;
        while(line[i] != '\n') {
            while (line[i] == ' ') {
                i++;
            }
            while (isdigit(line[i])) {
                dist = dist * 10 + line[i++] - '0';
            }
        }
    }
    for(int k= 1; k < (time / 2);k++) {
        if ((k *(time -k) > dist)) {
            acc++;
        }
    }
    acc *= 2;
    if (time % 2 == 0) {
        int k = time / 2 + 1;
        if ((k *(time -k) > dist)) {
            acc++;
        }
    }


    printf("The result is %ld\n",acc);
    fclose(file);
    return 0;
}


