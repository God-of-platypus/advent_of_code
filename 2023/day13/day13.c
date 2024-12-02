#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#define DIMENSION 32

typedef unsigned long BitVector;

bool bit_vector_is_pow_2(const BitVector instance)
{
  return instance > 0 && (instance & (instance - 1)) == 0;
}

void bit_matrix_clear(BitVector* instance)
{
  memset(instance, 0, DIMENSION * sizeof(BitVector));
}

bool mid_smudged(const BitVector* matrix, const int index) {
  int left = index;
  int right = index + 1;
  bool smudged = false;

  while (left >= 0 && matrix[right])
  {
    if (matrix[left] != matrix[right])
    {
      if (smudged || !bit_vector_is_pow_2(matrix[left] ^ matrix[right]))
      {
        return false;
      }

      smudged = true;
    }

    left--;
    right++;
  }

  return smudged;
}

bool mid(const BitVector* matrix, const int index)
{
  int left = index;
  int right = index + 1;

  while (left >= 0 && matrix[right])
  {
    if (matrix[left] != matrix[right])
    {
      return false;
    }

    left--;
    right++;
  }

  return true;
}

int realize(const BitVector* matrix, const bool smudged)
{
  for (int i = 0; matrix[i + 1]; i++)
  {
    const bool tmp = smudged ? mid_smudged(matrix, i) : mid(matrix, i);
    if (tmp)
    {
      return i + 1;
    }
  }

  return 0;
}

int realize_xy(const BitVector* x, const BitVector* y, bool smudged)
{
  const int result = realize(y, smudged);

  if (result)
  {
    return 100 * result;
  }

  return realize(x, smudged);
}

int main() {
  FILE *f = fopen("input.txt", "r");
  if (!f) {
    printf("Error opening file\n");
    return 1;
  }

  BitVector x[DIMENSION] = { 0 };
  BitVector y[DIMENSION] = { 0 };
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int count = 0;
  int count_smudged = 0;
  int i = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    if (line[0] == '\n') {
      i = 0;

      count += realize_xy(x,y, false);
      count_smudged += realize_xy(x, y, true);
      bit_matrix_clear(x);
      bit_matrix_clear(y);
      continue;
    }

    int j = 0;
    while (line[j] != '\n') {
      switch (line[j]) {
        case '.':
          y[i] <<= 1;
          x[j] <<= 1;
          break;
        case '#':
          y[i] = (y[i] << 1) | 1;
          x[j] = (x[j] << 1) | 1;
          break;
        default:
          return 1;
      }
      j++;
    }
    i++;
  }

  fclose(f);
  free(line);

  printf("%d\n", count);
  printf("%d\n", count_smudged);

  return 0;
}