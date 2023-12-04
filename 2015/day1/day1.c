#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>

int main(void) {
    char *line;
    long int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;
    int basement = 0;

    while ((nread = getline(&line, &len, file)) != -1) {
        int i = 0;
        while (line[i] != '\0' && line[i] != EOF) {
            if (line[i] == '(') {
                acc++;
            } else if (line[i] == ')') {
                acc--;
            }
            if (acc == -1 && basement == 0) {
                basement = i + 1;
            }
            ++i;
        }
    }
    printf("The result of part 1 is %ld\n", acc);
    printf("The result of part 2 is %d\n", basement);
}
