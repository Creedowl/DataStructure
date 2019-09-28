/*
 * @Date: 2019-09-28 14:26:42
 * @Author: creedowl
 * @Description: problem 2 using linked list
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int elemType;

typedef enum { SUCCESS, FAIL } status;

typedef struct LNode {
  elemType value;
  struct LNode *next;
} listNode, *listHead;

// initialize a sequential list
status initList(listHead *h) {
  // h is listHead's pointer that *h is head node
  *h = (listHead)malloc(sizeof(listNode));
  // memory limit exceeded
  if (!(*h)) {
    printf("FATAL: can't create list, memory limit exceeded\n");
    return FAIL;
  }
  // head node's value represents list's length
  (*h)->value = 0;
  (*h)->next = NULL;
  return SUCCESS;
}

// create a linked list by inputting elemType values
status createList(listHead *h, int length) {
  initList(h);
  elemType temp;
  // save head's pointer to update list length
  listHead pos = *h;
  for (int i = 0; i < length; i++) {
    printf("please input %d elements: ", length);
    scanf("%d", &temp);
    pos->next = (listNode *)malloc(sizeof(listNode));
    // memory limit exceeded
    if (!pos->next) {
      printf("FATAL: can't create list, memory limit exceeded\n");
      return FAIL;
    }
    // move pointer to the new node
    pos = pos->next;
    pos->value = temp;
    pos->next = NULL;
    (*h)->value++;
  }
  return SUCCESS;
}

// free all nodes and reset head to clear list
void clearList(listHead h) {
  listNode *temp, *pos = h->next;
  while (pos) {
    temp = pos->next;
    free(pos);
    pos = temp;
  }
  h->value = 0;
  h->next = NULL;
}

// free all nodes to destroy a list
void destroyList(listHead *h) {
  clearList(*h);
  free(*h);
}

void listReverse(listHead h) {
  listNode *head = h->next, *current = h->next;
  h->next = NULL;
  // while (tail->next != NULL) tail = tail->next;
  for (int i = 0; i < h->value; i++) {
    current = current->next;
    head->next = h->next;
    h->next = head;
    head = current;
  }
}

// print a list's properties
void printList(listHead h) {
  printf("------\n");
  printf("length: %d\n", h->value);
  for (h = h->next; h != NULL; h = h->next) {
    printf("%d ", h->value);
  }
  printf("\n------\n");
}

int main() {
  listHead linkList;
  int n;
  printf("please input list size\n");
  scanf("%d", &n);
  createList(&linkList, n);
  printList(linkList);
  listReverse(linkList);
  printList(linkList);
  destroyList(&linkList);
}