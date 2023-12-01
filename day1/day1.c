#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

int main(void) {
    char *line;
    long unsigned int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;

    while ((nread = getline(&line, &len, file)) != -1) {
        int first = -1;
        int last = 0;
        for(int i = 0; i < len && line[i] != '\0'; i++) {
            if (line[i] <= '9' && line[i] >= '0') {
                if (first == -1) {
                    first = line[i] - '0';
                   
                }
                last = line[i] - '0'; 
            } else if (line[i] == 'z' && strncmp("zero", line + i , 4) == 0) {
                if (first == -1) {
                    first = 0;

                }
                last = 0;
            } else if (line[i] == 'o' && strncmp("one", line + i, 3) == 0) {
                if (first == -1) {
                   first = 1;
                }
                last = 1;
            } else if (strncmp("two", line + i, 3) == 0) {
                if (first == -1) {
                    first = 2;
                }
                last = 2;
            } else if (strncmp("three", line + i, 4) == 0) {
                if (first == -1) {
                    first = 3;
                }
                last = 3;
            } else if (strncmp("four", line + i, 4) == 0) {
                if (first == -1) {
                    first = 4;
                }
                last = 4;
            } else if (strncmp("five", line + i, 4) == 0) {
                if (first == -1) {
                    first = 5;
                }
                last = 5;
            } else if (strncmp("six", line + i, 3) == 0) {
                if (first == -1) {
                    first = 6;
                }
                last = 6;
            } else if (strncmp("seven", line + i, 5) == 0){
                if (first == -1) {
                    first = 7;
                }
                last = 7;
            } else if (strncmp("eight", line + i, 5) == 0){
                if (first == -1) {
                    first = 8;
                }
                last = 8;
            } else if (strncmp("nine", line + i, 4) == 0){
                if (first == -1) {
                    first = 9;
                }
                last = 9;
            }
        }
        printf("The value of line %ld is %d\n", nbLine, first * 10 + last);
        acc += first * 10 + last;
        nbLine++;
    }
    printf("The result is %ld\n",acc);
    fclose(file);
    return 0;
}
