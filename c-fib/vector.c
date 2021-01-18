#include "vector.h"

void vector_init(Vector *a, size_t initialSize) {
  a->array = (unsigned int*) malloc(initialSize * sizeof(unsigned int));
  a->used = 0;
  a->capacity = initialSize;
}

void vector_insert(Vector *a, unsigned int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->capacity 
  if (a->used == a->capacity) {
    a->capacity *= 2;
    a->array = (unsigned int*) realloc(a->array, a->capacity * sizeof(unsigned int));
  }
  a->array[a->used++] = element;
}

void vector_free(Vector *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->capacity = 0;
}