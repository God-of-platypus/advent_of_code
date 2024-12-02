#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_GROUPS 20

// Function to check if the current arrangement satisfies the group sizes
int is_valid(char *row, int *group_sizes, int group_count) {
    int current_size = 0, group_index = 0;

    for (int i = 0; row[i] != '\0'; i++) {
        if (row[i] == '#') {
            current_size++;
        } else if (current_size > 0) {
            if (group_index >= group_count || current_size != group_sizes[group_index]) {
                return 0; // Group size mismatch
            }
            group_index++;
            current_size = 0;
        }
    }

    // Handle the final group
    if (current_size > 0) {
        if (group_index >= group_count || current_size != group_sizes[group_index]) {
            return 0;
        }
        group_index++;
    }

    return group_index == group_count;
}

// Backtracking function to count valid arrangements
void backtrack(char *row, int index, int *group_sizes, int group_count, int *count) {
    if (row[index] == '\0') {
        if (is_valid(row, group_sizes, group_count)) {
            (*count)++;
        }
        return;
    }

    if (row[index] == '?') {
        row[index] = '.';
        backtrack(row, index + 1, group_sizes, group_count, count);
        row[index] = '#';
        backtrack(row, index + 1, group_sizes, group_count, count);
        row[index] = '?';
    } else {
        backtrack(row, index + 1, group_sizes, group_count, count);
    }
}

// Function to count arrangements for a single row
int count_arrangements(char *row, int *group_sizes, int group_count) {
    int count = 0;
    backtrack(row, 0, group_sizes, group_count, &count);
    return count;
}

// Function to parse group sizes from a string
int parse_group_sizes(char *group_string, int *group_sizes) {
    int count = 0;
    char *token = strtok(group_string, ",");
    while (token) {
        group_sizes[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    return count;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LENGTH];
    int total = 0;

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Remove the newline character
        line[strcspn(line, "\n")] = '\0';

        // Split the row and group sizes
        char *row = strtok(line, " ");
        char *group_string = strtok(NULL, " ");

        if (!row || !group_string) {
            fprintf(stderr, "Invalid input format\n");
            continue;
        }

        // Parse group sizes
        int group_sizes[MAX_GROUPS];
        int group_count = parse_group_sizes(group_string, group_sizes);

        // Create a modifiable copy of the row
        char row_copy[MAX_LENGTH];
        strcpy(row_copy, row);

        // Count valid arrangements and add to total
        total += count_arrangements(row_copy, group_sizes, group_count);
    }

    fclose(file);

    printf("Total arrangements: %d\n", total);
    return 0;
}
