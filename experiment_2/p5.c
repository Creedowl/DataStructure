/*
 * @Date: 2019-10-17 22:09:31
 * @Author: creedowl
 * @Description: e2p5
 */
#include <stdio.h>
#include <stdlib.h>

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

// print a list's properties
void printList(listHead h) {
  printf("-----\n");
  printf("length: %d\n", h->value);
  for (h = h->next; h != NULL; h = h->next) {
    printf("%d ", h->value);
  }
  printf("\n------\n");
}

// merge to linked list(ascending order) into c (descending order)
void merge(listHead l1, listHead l2, listHead c) {
  listNode *p1 = l1->next, *p2 = l2->next, *temp;
  while (p1 || p2) {
    if (p1 && p1->value < p2->value) {
      temp = p1->next;
      p1->next = c->next;
      c->next = p1;
      p1 = temp;
    } else {
      temp = p2->next;
      p2->next = c->next;
      c->next = p2;
      p2 = temp;
    }
  }
  c->value = l1->value + l2->value;
  l1->value = 0;
  l2->value = 0;
  l1->next = NULL;
  l2->next = NULL;
}

int main() {
  listHead l1, l2, c;
  initList(&c);
  createList(&l1, 3);
  createList(&l2, 4);
  merge(l1, l2, c);
  printList(c);
  destroyList(&l1);
  destroyList(&l2);
  destroyList(&c);
}
