#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void update(char *line, int **array) {
    int i = 0;
    char str[16] = {0};

    while (line[i] != ' ') {
        str[i] = line[i];
        i++;
    }
    if (strncmp(str, "turn", 4) == 0) {
        str[i] = line[i++];
        while (line[i] != ' ') {
            str[i] = line[i++];
        }
    }
    int start_x = 0;
    int start_y = 0;
    int end_x = 0;
    int end_y = 0;
    while (line[i] == ' ') {
        i++;
    }
    while (isdigit(line[i])) {
        start_x = start_x * 10 + line[i] - '0';       
        i++;
    }
    i++;
    while (isdigit(line[i])) {
        start_y = start_y * 10 + line[i] - '0';
        i++;       
    }
    i++;
    while (line[i] != ' ') {
        i++;
    }
    i++;

    while (isdigit(line[i])) {
       end_x = end_x * 10 + line[i] - '0';
       i++;
    }
    i++;
    while (isdigit(line[i])) {
        end_y = end_y * 10 + line[i] - '0';
        i++;
    }
    i++;
    if (strncmp("toggle", str, 6) == 0) {
        for(i = start_x; i <= end_x; i++) {
            for(int j = start_y; j <= end_y; j++) {
                array[j][i] = 1 - array[j][i];
            }
        }
    } else if (strncmp("turn off", str, 8) == 0) {
        for(i = start_x; i <= end_x; i++) {
            for(int j = start_y; j <= end_y; j++) {
                array[j][i] = 0;
            }
        }
    } else if (strncmp("turn on", str, 7) == 0) {
        for(i = start_x; i <= end_x; i++) {
            for(int j = start_y; j <= end_y; j++) {
                array[j][i] = 1;
            }
        }
    }
}

int main(void) {
    char *line;
    long int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;

    int array[1000][1000] = {0};

    while ((nread = getline(&line, &len, file)) != -1) {
        int i = 0;
        char str[16] = {0};

        while (line[i] != ' ') {
            str[i] = line[i];
            i++;
        }
        if (strncmp(str, "turn", 4) == 0) {
            str[i] = line[i];
            i++;
            while (line[i] != ' ') {
                str[i] = line[i];
                i++;
            }
        }
        int start_x = 0;
        int start_y = 0;
        int end_x = 0;
        int end_y = 0;
        while (line[i] == ' ') {
            i++;
        }
        while (isdigit(line[i])) {
            start_x = start_x * 10 + line[i] - '0';       
            i++;
        }
        i++;
        while (isdigit(line[i])) {
            start_y = start_y * 10 + line[i] - '0';
            i++;       
        }
        i++;
        while (line[i] != ' ') {
            i++;
        }
        i++;

        while (isdigit(line[i])) {
           end_x = end_x * 10 + line[i] - '0';
           i++;
        }
        i++;
        while (isdigit(line[i])) {
            end_y = end_y * 10 + line[i] - '0';
            i++;
        }
        i++;
        if (strncmp("toggle", str, 6) == 0) {
            for(i = start_x; i <= end_x; i++) {
                for(int j = start_y; j <= end_y; j++) {
                    array[j][i] = 1 - array[j][i];
                }
            }
        } else if (strncmp("turn off", str, 8) == 0) {
            for(i = start_x; i <= end_x; i++) {
                for(int j = start_y; j <= end_y; j++) {
                    array[j][i] = 0;
                }
            }
        } else if (strncmp("turn on", str, 7) == 0) {
            for(i = start_x; i <= end_x; i++) {
                for(int j = start_y; j <= end_y; j++) {
                    array[j][i] = 1;
                }
            }
        }
        //update(line, (int **)array);
    }
    for(int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            acc += array[i][j];
        }
    }
    printf("The result of part 1 is %ld\n", acc);
}

