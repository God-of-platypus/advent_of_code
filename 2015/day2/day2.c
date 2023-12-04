#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char *line;
    long unsigned int acc = 0;
    long unsigned int ribbon = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;

    while ((nread = getline(&line, &len, file)) != -1) {
        int h = 0;
        int l = 0;
        int w = 0;

        int i = 0;
        while (isdigit(line[i])) {
            h = h * 10 + line[i++] - '0';
        }
        i++;
        while (isdigit(line[i])) {
            l = l * 10 + line[i++] - '0';
        }
        i++;
        while (isdigit(line[i])) {
            w = w * 10 + line[i++] - '0';
        }
        ribbon += h * w * l;
        if (h <= l && h <= w){
            if (l <= w) {
                ribbon += 2 * (l + h);
            } else {
                ribbon += 2 * (h + w);
            }
        } else if (l <= h && l <= w) {
            if (h <= w) {
                ribbon += 2 * (h + l);
            } else {
                ribbon += 2 * (l + w);
            }
        } else {
            if (l <= h) {
                ribbon += 2 * (w + l);
            } else {
                ribbon += 2 * (w + h);
            }
        }
        int slack = 0;
        slack = w * h > h * l ? h * l: w * h;
        slack = slack > w * l ? w * l: slack; 

        acc += 2 * (w * h + h * l + l * w) + slack;
    }
    printf("The result of part 1 is %ld\n", acc);
    printf("The result of part 2 is %ld\n", ribbon); 
}

