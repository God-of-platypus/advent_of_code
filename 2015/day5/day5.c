#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int check_double(char *string, int pos) {
    if (string[pos] == '\0' || string[pos + 1] == '\0') {
        return 0;
    }
    return string[pos] == string[pos +1];
}

int is_nice_part1(char * line) {
    char *bad[4] = {"ab", "cd", "pq", "xy"};
    int vowel_count = 0;
    int doubles = 0;
    int b = 0;
    for (size_t i = 0; i < strlen(line); i++) {
        if (i != strlen(line) - 1) {
            int need_break = 0;
            for (int j = 0; j < 4; j++) {
                if (strncmp(bad[j], line + i, 2) == 0) {
                    need_break++;
                    break;
                }
            }
            if (need_break) {
                b = 1;
                break;
            }
        }
        int res_double = check_double(line, i);
        doubles += res_double;
        switch (line[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                vowel_count++;
                break;
            default:
                break;
        }
    }
    return (doubles > 0 && vowel_count > 2 && b == 0);
}

int is_nice_part2(char *str) {
    int len = strlen(str);
    int has_pair = 0;
    int has_repeat_with_gap = 0;

    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 2; j < len - 1; j++) {
            if (str[i] == str[j] && str[i + 1] == str[j + 1]) {
                has_pair = 1;
                break;
            }
        }
        if (has_pair) {
            break;
        }
    }

    for (int i = 0; i < len - 2; i++) {
        if (str[i] == str[i + 2]) {
            has_repeat_with_gap = 1;
            break;
        }
    }

    return has_pair && has_repeat_with_gap;
}

int main(void) {
    char *line;
    long int acc1 = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int acc2 = 0;

    while ((nread = getline(&line, &len, file)) != -1) {
        if (is_nice_part1(line)) {
            acc1++;
        }
        if (is_nice_part2(line)) {
            acc2++;
        }
    }
    free(line);
    fclose(file);
    printf("The result of part 1 is %ld\n", acc1);
    printf("The result of part 2 is %ld\n", acc2);
}
