#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};

int main(void) {
    char *line;
    long int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;

    struct point **a = malloc(sizeof(struct point*));
    int l = 1;
    int x_s = 0;
    int y_s = 0;

    struct point *start = malloc(sizeof(struct point));
    start->x = 0;
    start->y = 0;
    a[0] = start;

    int x_r = 0;
    int y_r = 0;

    int turn = 0;

    while ((nread = getline(&line, &len, file)) != -1) {
        int i = 0;
        while (line[i] != '\0' && line[i] != EOF) {
            if (turn == 0) {
                if (line[i] == '^') {
                    x_s++;
                } else if (line[i] == '<') {
                    y_s--;
                } else if (line[i] == 'v') {
                    x_s--;
                } else if (line[i] == '>') {
                    y_s++;
                }
                int visited = 0;
                for (int j = 0; j < l; j++) {
                    if (a[j]->x == x_s && a[j]->y == y_s) {
                        visited = 1;
                    }
                }
                if (!visited) {
                    a = realloc(a ,(l+1) * sizeof(struct point));
                    struct point *new = malloc(sizeof(struct point));
                    new->x = x_s;
                    new->y = y_s;
                    a[l++] = new;
                }
                i++;
                turn = 1;
            } else {
                if (line[i] == '^') {
                    x_r++;
                } else if (line[i] == '<') {
                    y_r--;
                } else if (line[i] == 'v') {
                    x_r--;
                } else if (line[i] == '>') {
                    y_r++;
                }
                int visited = 0;
                for (int j = 0; j < l; j++) {
                    if (a[j]->x == x_r && a[j]->y == y_r) {
                        visited = 1;
                    }
                }
                if (!visited) {
                    a = realloc(a ,(l+1) * sizeof(struct point));
                    struct point *new = malloc(sizeof(struct point));
                    new->x = x_r;
                    new->y = y_r;
                    a[l++] = new;
                }
                i++;
                turn = 0;
            }
        }
    }
    for (int j = 0; j < l; j++) {
        free(a[j]);
    }
    free(a);
    fclose(file);
    free(line);
    printf("The result of part 2 is %d\n", l);
}

