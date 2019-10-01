/*
 * @Date: 2019-09-29 20:42:30
 * @Author: creedowl
 * @Description: problem 3 using linked list
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
  // save head's pointer to update list length
  listHead pos = *h;
  for (int i = 0; i < length; i++) {
    pos->next = (listNode *)malloc(sizeof(listNode));
    // memory limit exceeded
    if (!pos->next) {
      printf("FATAL: can't create list, memory limit exceeded\n");
      return FAIL;
    }
    // move pointer to the new node
    pos = pos->next;
    pos->value = i + 1;
    pos->next = NULL;
    (*h)->value++;
  }
  pos->next = (*h)->next;
  return SUCCESS;
}

void solve(listHead h, int m) {
  listNode *pos = h->next, *pre;
  int length = h->value;
  while (h->value--) {
    for (int i = 0; i < m - 1; i++) {
      pre = pos;
      pos = pos->next;
    }
    printf("%d ", pos->value);
    // delete node
    pre->next = pos->next;
    free(pos);
    // set NULL after deleting the last node to avoid invalid read
    pos = h->value <= 0 ? NULL : pre->next;
  }
  printf("\n");
}

int main() {
  int m, n;
  scanf("%d%d", &n, &m);
  listHead linklist;
  createList(&linklist, n);
  solve(linklist, m);
  free(linklist);
}
