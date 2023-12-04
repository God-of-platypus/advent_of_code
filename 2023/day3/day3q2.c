#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


int find_num(char **map, int i, int j) {
    int acc = 0;
    while (j != 0 && isdigit(map[i][j-1])){
        j--;
    }

    while(j!= 140 && isdigit(map[i][j])) {
        acc = acc * 10 + map[i][j] - '0';
        j++;
    }
    return acc;
}

bool gear(char **map, int i, int j, int *acc) {
    int count = 0;
    int array[8] = {0};
    if (j != 0) {
        if (isdigit(map[i][j-1])) {
            array[count++] = find_num(map, i, j-1);
        }
    } if (j != 139){
        if (isdigit(map[i][j+1])) {
            array[count++] = find_num(map, i, j+1);
        }
    }
    if (i != 139) {
        if (j == 0) {
            if (isdigit(map[i+1][j]) && isdigit(map[i+1][j+1])) {
                array[count++] = find_num(map, i+1, j+1);
            } else if (isdigit(map[i+1][j])) {
                array[count++] = find_num(map, i+1, j);
            } else if (isdigit(map[i+1][j+1])) {
                array[count++] = find_num(map, i+1, j+1);
            }
        } else if (j == 139) {
            if (isdigit(map[i+1][j]) && isdigit(map[i+1][j-1])) {
                array[count++] = find_num(map, i+1, j);
            } else if (isdigit(map[i+1][j])) {
                array[count++] = find_num(map, i+1, j);
            } else if (isdigit(map[i+1][j-1])) {
                array[count++] = find_num(map, i+1, j-1);
            }
        } else {
            if (isdigit(map[i+1][j]) && isdigit(map[i+1][j-1]) && isdigit(map[i+1][j+1])) {
                array[count++] = find_num(map, i+1, j+1);
            } else if (isdigit(map[i+1][j]) && isdigit(map[i+1][j+1])) {
                array[count++] = find_num(map, i+1, j+1);
            } else if (isdigit(map[i+1][j-1]) && isdigit(map[i+1][j])) {
                array[count++] = find_num(map, i+1, j);
            } else if (isdigit(map[i+1][j-1]) && isdigit(map[i+1][j+1])) {
                array[count++] = find_num(map, i+1, j-1);
                array[count++] = find_num(map, i+1, j+1);
            } else if (isdigit(map[i+1][j-1])) {
                array[count++] = find_num(map, i+1, j-1);
            } else if (isdigit(map[i+1][j])) {
                array[count++] = find_num(map, i+1, j);
            } else if (isdigit(map[i+1][j+1])) {
                array[count++] = find_num(map, i+1,j+1);
            }
        }
    } if (i != 0) {
        if (j == 0) {
            if (isdigit(map[i+1][j]) && isdigit(map[i-1][j+1])) {
                array[count++] = find_num(map, i-1, j+1);
            } else if (isdigit(map[i-1][j])) {
                array[count++] = find_num(map, i-1, j);
            } else if (isdigit(map[i-1][j+1])) {
                array[count++] = find_num(map, i-1, j+1);
            }
        } else if (j == 139) {
            if (isdigit(map[i-1][j]) && isdigit(map[i-1][j-1])) {
                array[count++] = find_num(map, i-1, j);
            } else if (isdigit(map[i-1][j])) {
                array[count++] = find_num(map, i-1, j);
            } else if (isdigit(map[i-1][j-1])) {
                array[count++] = find_num(map, i-1, j-1);
            }
        } else {
            if (isdigit(map[i-1][j]) && isdigit(map[i-1][j-1]) && isdigit(map[i-1][j+1])) {
                array[count++] = find_num(map, i-1, j+1);
            } else if (isdigit(map[i-1][j]) && isdigit(map[i-1][j+1])) {
                array[count++] = find_num(map, i-1, j+1);
            } else if (isdigit(map[i-1][j-1]) && isdigit(map[i-1][j])) {
                array[count++] = find_num(map, i-1, j);
            } else if (isdigit(map[i-1][j-1]) && isdigit(map[i-1][j+1])) {
                array[count++] = find_num(map, i-1, j-1);
                array[count++] = find_num(map, i-1, j+1);
            } else if (isdigit(map[i-1][j-1])) {
                array[count++] = find_num(map, i-1, j-1);
            } else if (isdigit(map[i-1][j])) {
                array[count++] = find_num(map, i-1, j);
            } else if (isdigit(map[i-1][j+1])) {
                array[count++] = find_num(map, i-1,j+1);
            }
        }
    }
    map[i][j] == '.';
    if (count != 2) {
        return false;
    }
    *acc = array[0] * array[1];
    return true;
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
            if (map[i][j] == '*') {
                int accu = 0;
                bool res = gear(map,i,j,&accu);
                if (res) {
                    acc += accu;
                }
            } 
        }
    }
    printf("The result is %ld\n", acc);
}
