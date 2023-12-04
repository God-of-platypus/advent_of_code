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
    int x = 0;
    int y = 0;

    struct point *start = malloc(sizeof(struct point));
    start->x = 0;
    start->y = 0;
    a[0] = start;

    while ((nread = getline(&line, &len, file)) != -1) {
        int i = 0;
        while (line[i] != '\0' && line[i] != EOF) {
            if (line[i] == '^') {
                x++;
            } else if (line[i] == '<') {
                y--;
            } else if (line[i] == 'v') {
                x--;
            } else if (line[i] == '>') {
                y++;
            }
            int visited = 0;
            for (int j = 0; j < l; j++) {
                if (a[j]->x == x && a[j]->y == y) {
                    visited = 1;
                }
            }
            if (!visited) {
                a = realloc(a ,(l+1) * sizeof(struct point));
                struct point *new = malloc(sizeof(struct point));
                new->x = x;
                new->y = y;
                a[l++] = new;
            }
            i++;
        }
    }
    for (int j = 0; j < l; j++) {
        free(a[j]);
    }
    free(a);
    fclose(file);
    free(line);
    printf("The result of part 1 is %d\n", l);
}
