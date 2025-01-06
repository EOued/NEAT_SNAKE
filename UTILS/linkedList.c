#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

doublyLinkedList* initList()
{
  doublyLinkedList* list;
  if (!(list = malloc(sizeof(doublyLinkedList)))) return NULL;
  list->start = NULL;
  list->end   = NULL;
  list->size  = 0;
  return list;
}
void freeList(doublyLinkedList* list)
{
  if (!list) return;
  struct Node* toDel = list->start;
  struct Node* temp;
  while (toDel)
  {
    temp = toDel->next;
    free(toDel);
    toDel = temp;
  }
  free(list);
}
int isEmpty(doublyLinkedList* list)
{
  if (!list) return 0;
  return !list->start && !list->end;
}
void prepend(doublyLinkedList* list, int x, int y, int orientation)
{
  if (!list) return;
  struct Node* node;
  if (!(node = malloc(sizeof(struct Node)))) return;
  node->x           = x;
  node->y           = y;
  node->orientation = orientation;
  node->next        = list->start;
  node->before      = NULL;
  if (list->start) list->start->before = node;
  list->start = node;
  if (!list->end) list->end = list->start;
  list->size++;
  return;
}
void append(doublyLinkedList* list, int x, int y, int orientation)
{
  if (!list) return;
  struct Node* node;
  if (!(node = malloc(sizeof(struct Node)))) return;
  node->x           = x;
  node->y           = y;
  node->orientation = orientation;
  node->next        = NULL;
  node->before      = list->end;
  if (list->end) list->end->next = node;
  list->end = node;
  if (!list->start) list->start = list->end;
  list->size++;
  return;
}
void deleteStart(doublyLinkedList* list)
{
  if (!list) return;
  struct Node* toDel = list->start;
  if (!toDel) return;
  list->start = list->start->next;
  if (list->start) list->start->before = NULL;
  free(toDel);
  list->size--;
  return;
}

void deleteEnd(doublyLinkedList* list)
{
  if (!list) return;
  struct Node* toDel = list->end;
  if (!toDel) return;
  list->end = list->end->before;
  if (list->end) list->end->next = NULL;
  free(toDel);
  list->size--;
  return;
}

int searchInList(doublyLinkedList* list, int x, int y, int orientation)
{
  if (!list) return 0;
  struct Node* temp = list->start;
  if (!temp) return 0;
  while (temp && (temp->x != x || temp->y != y || temp->orientation != orientation))
    temp = temp->next;
  return temp != NULL;
}

void printList(doublyLinkedList* list)
{
  if (!list) return;
  struct Node* temp = list->start;
  if (!temp) return;
  while (temp)
  {
    printf("%d %d |", temp->x, temp->y);
    temp = temp->next;
  }
  return;
}

void deleteElement(doublyLinkedList* list, int x, int y, int orientation)
{
  if (!list || (!list->start && !list->end)) return;
  if (list->start->x == x && list->start->y == y && list->start->orientation == orientation)
  {
    deleteStart(list);
    return;
  }
  if (list->end->x == x && list->end->y == y && list->end->orientation == orientation)
  {
    deleteEnd(list);
    return;
  }
  struct Node* temp = list->start->next;
  while (temp)
  {
    if (temp->x == x && temp->y == y) break;
    temp = temp->next;
  }
  if (!temp) return;
  struct Node* bef  = temp->before;
  struct Node* next = temp->next;
  bef->next         = temp->next;
  next->before      = temp->before;
  free(temp);
  list->size--;
  return;
}

struct Node* getNthElement(doublyLinkedList* list, unsigned int n)
{
  if (!list || !list->start) return NULL;
  struct Node* temp = list->start;
  int x             = n;
  while (temp && x != 0)
  {
    temp = temp->next;
    x--;
  }
  return temp ? temp : NULL;
}
