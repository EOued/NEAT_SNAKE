#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct Node
{
  int x;
  int y;
  int orientation;
  struct Node* next;
  struct Node* before;
};

typedef struct
{
  int size;
  struct Node* start;
  struct Node* end;
} doublyLinkedList;

doublyLinkedList* initList();
void freeList(doublyLinkedList* list);
int isEmpty(doublyLinkedList* list);
void prepend(doublyLinkedList* list, int x, int y, int orientation);
void append(doublyLinkedList* list, int x, int y, int orientation);
void deleteStart(doublyLinkedList* list);
void deleteEnd(doublyLinkedList* list);
int searchInList(doublyLinkedList* list, int x, int y, int orientation);
void deleteElement(doublyLinkedList* list, int x, int y, int orientation);
void printList(doublyLinkedList* list);
struct Node* getNthElement(doublyLinkedList* list, unsigned int n);
#endif
