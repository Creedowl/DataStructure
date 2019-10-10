/*
 * @Date: 2019-10-10 14:58:09
 * @Author: creedowl
 * @Description: e1p8, O(n)
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

void solve(listHead h, int mi, int ma) {
  listNode *pos = h, *temp;
  while (pos->next != NULL) {
    if (pos->next->value > mi && pos->next->value < ma) {
      temp = pos->next;
      pos->next = temp->next;
      free(temp);
      h->value--;
    } else {
      pos = pos->next;
    }
  }
}

int main() {
  listHead h;
  int mink, maxk;
  scanf("%d%d", &mink, &maxk);
  createList(&h, 10);
  solve(h, mink, maxk);
  printList(h);
  destroyList(&h);
}
