#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

int check_zero(int64_t *arr, int32_t len) {
    for(int32_t i = 0; i < len; i++) {
        if (arr[i] != 0) {
            return 1;
        }
    }
    return 0;
}


int main(void) {
    char *line;
    long int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;


    while ((nread = getline(&line, &len, file)) != -1) {
        int64_t **array = malloc(sizeof(int64_t *));
        int32_t len_array = 0;
        int32_t len_arr = 0;
        int64_t *arr = malloc(sizeof(int64_t));

        int i = 0;
        while (line[i] != '\n') {
            while(line[i] == ' ') {
                i++;
            }
            int mul = 1;
            if (line[i] == '-') {
                mul = -1;
                i++;
            }
            int64_t acc = 0;
            while(isdigit(line[i])) {
                acc = acc * 10 + line[i++] - '0';
            }
            acc *= mul;
            arr[len_arr++] = acc;
            int64_t *tmp = realloc(arr, (len_arr + 1) * sizeof(int64_t));
            if (tmp != arr) {
                arr = tmp;
            }
        }
        array[len_array++] = arr;
        int64_t **tmp = realloc(array, (len_array + 1) * sizeof(int64_t*));
        if (tmp != array) {
            array = tmp;
        }

        while (check_zero(array[len_array - 1], len_arr - len_array + 1)) {
            int64_t *a = malloc(sizeof(int64_t) * (len_arr - len_array));
            for (int32_t j = 0; j < len_arr  - len_array; j++) {
                a[j] = array[len_array - 1][j+1] - array[len_array -1][j];
            }
            array[len_array++] = a;
            int64_t **tmp = realloc(array, (len_array + 1) * sizeof(int64_t*));
            if (tmp != array) {
                array = tmp;
            }
        }
        int64_t k = 0;
        i = 1;
        for(int32_t j = len_array - 2; j >= 0; j--) {
            k = array[j][0] - k;
        }
        acc += k;
        for(int32_t j = 0; j < len_array; j++) {
            free(array[j]);
        }
        free(array);
        printf("Line number %ld has been treated\n\n", nbLine++);
    }
    fclose(file);
    free(line);
    printf("The result of part 2 is %ld\n", acc);
}


