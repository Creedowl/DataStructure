/*
 * @Date: 2019-10-19 11:08:17
 * @Author: creedowl
 * @Description: e2p7
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

void solve(listHead a, listHead b, listHead c) {
  listNode *temp, *head = a;
  while (a->next && b->next && c->next) {
    if (b->next->value == c->next->value) {
      while (a->next && a->next->value < b->next->value) {
        a = a->next;
      }
      if (a->next->value == b->next->value) {
        temp = a->next;
        a->next = temp->next;
        free(temp);
        head->value--;
      }
      b = b->next;
      c = c->next;
    } else if (b->next->value < c->next->value) {
      b = b->next;
    } else {
      c = c->next;
    }
  }
}

int main() {
  listHead a, b, c;
  createList(&a, 5);
  createList(&b, 4);
  createList(&c, 3);
  solve(a, b, c);
  printList(a);
  destroyList(&a);
  destroyList(&b);
  destroyList(&c);
}
