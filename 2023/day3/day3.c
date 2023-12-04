#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool dry(char **map, int i, int j, int *acc) {
    if (map[i][j] >= '0' && map[i][j] <= '9') {
        *acc = *acc * 10 + map[i][j] - '0';
        map[i][j] = '.';
    }
    bool res = false;
    if (i != 139) {
        res = res || (!isdigit(map[i+1][j]) && map[i+1][j] != '.') ;
        if (j != 0) {
            res = res || (!isdigit(map[i+1][j-1]) && map[i+1][j-1] != '.');    
        }
        if (j != 139) {
            res = res || (!isdigit(map[i+1][j+1]) && map[i+1][j+1] != '.');    
        }
    }
    if (i != 0) {
        res = res || (!isdigit(map[i-1][j]) && map[i-1][j] != '.');
        if (j != 0) {
            res = res || (!isdigit(map[i-1][j-1]) && map[i-1][j-1] != '.');    
        }
        if (j != 139) {
            res = res || (!isdigit(map[i-1][j+1]) && map[i-1][j+1] != '.');    
        }
    }
    if (j != 0) {
        res = res || (!isdigit(map[i][j-1]) && map[i][j-1] != '.');    
    }
    if (j != 139){
       res = res || (!isdigit(map[i][j+1]) && map[i][j+1] != '.');    
    } 
    if (j != 139 && isdigit(map[i][j+1])) {
        res = dry(map, i, j+1,acc) || res;
    }
    return res;
}

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 0;
    char **map = malloc(sizeof(char*) * 140);


    while ((nread = getline(&line, &len, file)) != -1) {
        char *l = malloc(sizeof(char) * 140);
        memcpy(l,line,140);
        map[nbLine++] = l;
    }
    fclose(file);
    free(line);

    int res = 0;
    for(int i = 0; i < 140; i++) {
        for (int j = 0; j< 140; j++) {
            if (isdigit(map[i][j])) {
                int accu = 0;
                bool res = dry(map,i,j,&accu);
                if (res) {
                    acc += accu;
                }
            } 
        }
    }
    printf("The result is %ld\n", acc);
}
