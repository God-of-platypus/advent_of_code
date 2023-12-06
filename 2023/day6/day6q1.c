#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;

    int *time = malloc(sizeof(int));
    int len_time = 0;

    int *dist = malloc(sizeof(int));
    int len_dist = 0;

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
            int acc = 0;
            while (isdigit(line[i])) {
                acc = acc * 10 + line[i++] - '0';
            }
            time[len_time] = acc;
            len_time++;
            int *tmp = realloc(time, (len_time + 1) * sizeof(int));
            if (tmp != time) {
                time = tmp;
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
            int acc = 0;
            while (isdigit(line[i])) {
                acc = acc * 10 + line[i++] - '0';
            }
            dist[len_dist] = acc;
            len_dist++;
            int *tmp = realloc(dist, (len_dist + 1) * sizeof(int));
            if (tmp != time) {
                dist = tmp;
            } 
        }
    }
    for (int j = 0; j < len_time; j++) {
        int t = time[j];
        int d = dist[j];
        int res = 0;
        for (int k = 0; k <= t; k++) {
            if (((k * (t - k)) > d)) {
                res++;
            } 
        }
        if (acc == 0) {
            acc = res;
        } else {
            acc *= res;
        }
    }


    printf("The result is %ld\n",acc);
    fclose(file);
    return 0;
}

