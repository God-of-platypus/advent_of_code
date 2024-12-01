#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

// Define constants
#define MAX_ROWS 140
#define MAX_COLS 140
#define TIME 1000000

typedef struct Galaxy
{
    uint64_t x;
    uint64_t y;
} Galaxy;


int main() {
    // Open the file containing the maze
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char cosmos[MAX_ROWS][MAX_COLS];
    int rows = 0, cols = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        line[read - 1] = '\0'; // Remove the newline character at the end of each line
        strncpy(cosmos[rows], line, MAX_COLS);
        if (cols < read - 1) {
            cols = read - 1; // Update column size if necessary
        }
        rows++;
    }
    free(line);
    fclose(file);

    bool empty_rows[MAX_ROWS] = {0};
    bool empty_cols[MAX_COLS] = {0};
    Galaxy galaxies[MAX_COLS * MAX_ROWS] = {0};

    int nb_galaxies = 0;
    for (int y = 0; y < rows; ++y) {
        bool empty = true;
        for (int x = 0; x < cols; ++x) {
            if (cosmos[y][x] == '#') {
                galaxies[nb_galaxies].x = x;
                galaxies[nb_galaxies].y = y;
                nb_galaxies++;
                empty_rows[y] = true;
                empty_cols[x] = true; 
            }
        }
    }
    printf("There is %d galaxies\n", nb_galaxies);

    for (int i = 0; i < nb_galaxies; i++) {
        Galaxy tmp = galaxies[i];
        for (int j = 0; j < tmp.x; j++) {
            if (!empty_cols[j])
                galaxies[i].x += TIME - 1;
        }
        for (int j = 0; j < tmp.y; j++) {
            if (!empty_rows[j])
                galaxies[i].y += TIME - 1;
        }
    }
    uint64_t res = 0;
    for (int i = 0; i < nb_galaxies; i++) {
        for (int j = i + 1; j < nb_galaxies; ++j) {
            res += galaxies[i].x > galaxies[j].x ? galaxies[i].x -galaxies[j].x : galaxies[j].x - galaxies[i].x;
            res += galaxies[i].y > galaxies[j].y ? galaxies[i].y -galaxies[j].y : galaxies[j].y - galaxies[i].y;
        }
    }

    printf("The total distances is %ld\n", res);

    return 0;
}