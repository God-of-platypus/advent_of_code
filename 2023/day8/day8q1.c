#define _POSIX_C_SOURCE 200810L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
        i += 4;
        char *left = calloc(4,sizeof(char));
        k = 0;

        while (line[i] != ',') {
            left[k++] = line[i++];
        }
        i+=2;

        char *right = calloc(4,sizeof(char));
        k = 0;

        while (line[i] != ')') {
            right[k++] = line[i++];
        }
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
    while (strcmp(graph[pos]->key, "ZZZ") != 0) {
        if (dir[mouv] == 'R') {
            pos = search(graph,len_graph, graph[pos]->right);
            mouv++;
        } else {
            pos = search(graph,len_graph, graph[pos]->left);
            mouv++;
        }
        if (strcmp(graph[pos]->key, "ZZZ") == 0)
        {
            printf("Found at mouv number %d\n",mouv);        
        }
        mouv = mouv % strlen(dir);
        acc++;
    }
    printf("The result of part 1 is %ld\n", acc);
}

