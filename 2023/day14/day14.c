#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIMENSION 100
#define LOOP 1000000000
#define DICTIONARY_BUCKETS 193
#define KEY_SIZE DIMENSION * DIMENSION

struct DictionaryEntry
{
  struct DictionaryEntry* nextEntry;
  long value;
  char key[KEY_SIZE];
};

struct DictionaryBucket
{
  struct DictionaryEntry* firstEntry;
  struct DictionaryBucket* nextBucket;
};

struct Dictionary
{
  struct DictionaryBucket* firstBucket;
  struct DictionaryBucket buckets[DICTIONARY_BUCKETS];
};

typedef struct DictionaryEntry* DictionaryEntry;
typedef struct DictionaryBucket* DictionaryBucket;
typedef struct Dictionary* Dictionary;

bool dictionary_replace(
    Dictionary instance,
    char key[],
    long* existingValue,
    long newValue)
{
  DictionaryEntry* p;
  unsigned int hash = 7;

  for (int i = 0; i < KEY_SIZE; i++)
  {
    hash = (hash * 31) + key[i];
  }

  hash %= DICTIONARY_BUCKETS;

  for (p = &instance->buckets[hash].firstEntry; *p; p = &(*p)->nextEntry)
  {
    if (memcmp(key, (*p)->key, KEY_SIZE) == 0)
    {
      *existingValue = (*p)->value;
      (*p)->value = newValue;

      return true;
    }
  }

  DictionaryEntry entry = malloc(sizeof *entry);

  if (!entry)
  {
    return false;
  }

  if (!instance->buckets[hash].firstEntry)
  {
    DictionaryBucket first = instance->firstBucket;

    instance->buckets[hash].nextBucket = first;
    instance->firstBucket = instance->buckets + hash;
  }

  memcpy(entry->key, key, KEY_SIZE);

  entry->value = newValue;
  entry->nextEntry = NULL;
  *p = entry;

  return true;
}

void dictionary_clear(Dictionary instance)
{
  for (DictionaryBucket bucket = instance->firstBucket;
      bucket;
      bucket = bucket->nextBucket)
  {
    DictionaryEntry entry = bucket->firstEntry;

    while (entry)
    {
      DictionaryEntry nextEntry = entry->nextEntry;

      free(entry);

      entry = nextEntry;
    }

    bucket->firstEntry = NULL;
  }

  instance->firstBucket = NULL;
}

void apply_gravity(char map[DIMENSION + 1][DIMENSION + 1], int row, int col) {
  for (int i = 1; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (map[i][j] == 'O') {
        int k = i -1;
        while (k >= 0 && map[k][j] == '.') {
          map[k+1][j] = '.';
          map[k][j] = 'O';
          k--;
        }
      }
    }
  }
}

void apply_south_gravity(char map[DIMENSION + 1][DIMENSION + 1], int row, int col) {
  for (int i = 1; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (map[i][j] == 'O') {
        int k = i + 1;
        while (k < row && map[k][j] == '.') {
          map[k-1][j] = '.';
          map[k][j] = 'O';
          k++;
        }
      }
    }
  }
}

void apply_west_gravity(char map[DIMENSION + 1][DIMENSION + 1], int row, int col) {
  for (int j = 1; j < col; j++) {
    for (int i = 1; i < row; i++) {
      if (map[i][j] == 'O') {
        int k = j - 1;
        while (k >= 0 && map[i][k] == '.') {
          map[i][k] = 'O';
          map[i][k + 1] = '.';
          k--;
        }
      }
    }
  }
}

void apply_east_gravity(char map[DIMENSION + 1][DIMENSION + 1], int row, int col) {
  for (int j = 1; j < col; j++) {
    for (int i = 1; i < row; i++) {
      if (map[i][j] == 'O') {
        int k = j + 1;
        while (k < col && map[i][k] == '.') {
          map[i][k] = 'O';
          map[i][k - 1] = '.';
          k++;
        }
      }
    }
  }
}

int get_result(char map[DIMENSION + 1][DIMENSION + 1], int row) {
  int result = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j <= strlen(map[i]); j++) {
      if (map[i][j] == 'O') {
        result += row - i;
      }
    }
  }
  return result;
}



int main() {
  FILE *f = fopen("input.txt", "r");
  if (!f) {
    printf("File could not be opened\n");
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char map[DIMENSION+1][DIMENSION + 1] = {0};

  int rows = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    if (line[0] == '\n') {
      continue;
    }
    //printf("%s", line);
    line[read - 1] = '\0';
    strncpy(map[rows++], line, read - 1);
  }
  fclose(f);
  free(line);
  apply_gravity(map, rows, strlen(map[0]) + 1);
  printf("Total load is: %d\n", get_result(map, rows));


  return 0;
}