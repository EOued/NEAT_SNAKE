#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <stdlib.h>

void sort(void* list, int (*isGreater)(void*, void*), size_t elem_size, int size);

#endif
