#pragma once
// gratitude to https://stackoverflow.com/a/3536261
#include <stdlib.h>

typedef struct {
  unsigned int *array;
  size_t used;
  size_t capacity;
} Vector;

void vector_init(Vector *a, size_t initialSize);

void vector_insert(Vector *a, unsigned int element);

void vector_free(Vector *a);