#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    char *key;
    char *left;
    char *right;
} node;

int comp(const void *n1, const void *n2) {
    const node *n11 = n1;
    const node *n22 = n2;
    int r = strcmp(n11->key,n22->key);
    if (r > 0) 
        return 1;
    else if (r < 0) 
        return -1;
    else 
        return 0;
}

void sort(node **arr, int len) {
    int i,j;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            node *a = arr[j];
            node *b = arr[j+1];
            if (strcmp(a->key, b->key) > 0) {
                arr[j] = b;
                arr[j +1] = a;
            }
        }
    }
}

int search(node **graph, int len, char *str) {
    int start = 0;
    int end = len - 1;
    while (start <= end ) {
        int m = start + (end -start) /2;

        if (strcmp(graph[m]->key, str) == 0) 
        {
            return m;
        }
        if (strcmp(graph[m]->key, str) < 0) {
            start = m + 1;
        } else {
            end = m - 1;
        }
    }
    return -1;

}

uint64_t gcd(uint64_t a, uint64_t b) {
    int temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return  (a /  gcd(a,b)) * b;
}


int main(void) {
    char *line;
    long int acc = 0;
    FILE *file = fopen("input.txt", "r");
    size_t len = 0;
    ssize_t nread;
    long unsigned int nbLine = 1;

    nread = getline(&line,&len,file);
    char *dir = malloc(strlen(line) * sizeof(char));
    for(int i = 0; i < strlen(line)-1; i++){
        dir[i] = line[i];
    }
    dir[strlen(line) - 1] = '\0';

    node **graph = malloc(sizeof(node *));
    int len_graph = 0;

    while ((nread = getline(&line, &len, file)) != -1) {
        if (line[0] == '\n') {
            continue;
        }
        int i = 0;
        int k = 0;
        char *key = calloc(4,sizeof(char));
        while (line[i] != ' ') {
            key[k++] = line[i++];
        }
        char a = key[0];
        key[0] = key[2];
        key[2] = a;
        i += 4;
        char *left = calloc(4,sizeof(char));
        k = 0;

        while (line[i] != ',') {
            left[k++] = line[i++];
        }
        i+=2;
        a = left[0];
        left[0] = left[2];
        left[2] = a; 

        char *right = calloc(4,sizeof(char));
        k = 0;

        while (line[i] != ')') {
            right[k++] = line[i++];
        }
        a = right[0];
        right[0] = right[2];
        right[2] = a;

        node *tmp = malloc(sizeof(node));
        tmp->key = key;
        tmp->left = left;
        tmp->right = right;
        graph[len_graph++] = tmp;
        node **t = realloc(graph, (len_graph + 1) * sizeof(node));
        if (t != graph) {
            graph = t;
        }
    }
    sort(graph, len_graph);
    /*
    for (int i = 0; i < len_graph;i++) {
        printf("%s = (%s, %s)\n", graph[i]->key, graph[i]->left, graph[i]->right);
    }
    */
    int pos = 0;
    int mouv = 0;

    node **a = malloc(sizeof(node *));
    int len_a = 0;
    while(graph[pos]->key[0] == 'A') {
        a[len_a++] = graph[pos];
        pos++;
        node **t = realloc(a, (len_a + 1) * sizeof(node));
        if (t != a) {
            a = t;
        }

    }
    pos = 0;
    uint64_t *arr = calloc(len_a,sizeof(uint64_t));
    for (int i = 0; i < len_a; i++) {
        while (a[i]->key[0] != 'Z') {
            int p = 0;
            if (dir[mouv] == 'R') {

                p = search(graph,len_graph, a[i]->right);
            } else {
                p = search(graph,len_graph, a[i]->left);
            }
            a[i] = graph[p]; 
            mouv++;
            mouv = mouv % strlen(dir);
            arr[i]++;
        }
    }
    uint64_t res = arr[0];
    for(int i = 1; i < len_a; i++) {
        res = lcm(res, arr[i]);
    }
    printf("The result of part 2 is %ld\n", res);
}


