#include "quicksort.h"
#include "errors.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(void* list, int (*isGreater)(void*, void*), size_t elem_size, int size)
{
  if (size <= 1) return;
  if (size == 2)
  {
    if (!isGreater(list, list + elem_size)) return;
    void* temp;
    memcpy(temp, list, elem_size);
    memcpy(list, list + elem_size, elem_size);
    memcpy(list + elem_size, temp, elem_size);
    return;
  }
  int pivotIndex = rand() % size;
  void* subList1 = malloc(size * elem_size);
  void* subList2 = malloc(size * elem_size);
  if (!subList1 || !subList2) sendError("Can't allocate memory for malloc of sort function.", 1);
  int subList1Size = 0;
  int subList2Size = 0;
  // Splitting list
  for (int i = 0; i < size; i++)
    if (isGreater(list + i * elem_size, list + pivotIndex * elem_size))
      memcpy(subList2 + (subList2Size++) * elem_size, list + i * elem_size, elem_size);
    else
      memcpy(subList1 + (subList1Size++) * elem_size, list + i * elem_size, elem_size);
  // Recursive sort
  sort(subList1, isGreater, elem_size, subList1Size);
  sort(subList2, isGreater, elem_size, subList2Size);
  for (int i = 0; i < size; i++)
    if (i < subList1Size) memcpy(list + i * elem_size, subList1 + i * elem_size, elem_size);
    else
      memcpy(list + i * elem_size, subList2 + (i - subList1Size) * elem_size, elem_size);
  free(subList1);
  free(subList2);
  return;
}
