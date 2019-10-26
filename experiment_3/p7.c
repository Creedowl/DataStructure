/*
 * @Date: 2019-10-25 23:07:23
 * @Author: creedowl
 * @Description: e3p7 2.37
 */
#include <stdio.h>
#include <stdlib.h>

typedef int elemType;

typedef struct LNode {
  elemType data;
  struct LNode *prior, *next;
} listNode, listHead;

int initList(listHead *h) {
  h->data = 0;
  h->prior = NULL;
  h->next = NULL;
  return 1;
}

int createList(listHead *h, int length) {
  initList(h);
  listNode *node, *currernt = h;
  int temp;
  for (size_t i = 0; i < length; i++) {
    scanf("%d", &temp);
    node = (listNode *)malloc(sizeof(listNode));
    if (!h) {
      printf("FATAL: can't create list, memory limit exceeded\n");
      return 0;
    }
    node->data = temp;
    node->prior = currernt;
    node->next = NULL;
    currernt->next = node;
    currernt = currernt->next;
    h->data++;
  }
  h->next->prior = currernt;
  currernt->next = h->next;
  return 1;
}

void destroyList(listHead *h) {
  listNode *temp, *pos = h->next;
  for (size_t i = 0; i < h->data; i++) {
    temp = pos->next;
    free(pos);
    pos = temp;
  }
  h->data = 0;
  h->prior = NULL;
  h->next = NULL;
}

void printList(listHead *h) {
  listNode *pos = h->next;
  printf("list size: %d\n", h->data);
  for (size_t i = 0; i < h->data; i++) {
    printf("prior: %d, next: %d, data: %d\n", pos->prior->data, pos->next->data,
            pos->data);
    pos = pos->next;
  }
}

void solve(listHead *h) {
  listNode *head = h, *tail = h->next->prior, *temp;
  int length = h->data % 2 ? h->data : h->data - 1;
  for (size_t i = 0; i < length; i++) {
    if (i % 2) {
      // remove node
      temp = head->next;
      head->next = temp->next;
      temp->next->prior = head;
      // insert node
      tail->next->prior = temp;
      temp->next = tail->next;
      temp->prior = tail;
      tail->next = temp;
    } else {
      head = head->next;
    }
  }
}

int main() {
  listHead h;
  createList(&h, 5);
  printList(&h);
  solve(&h);
  printList(&h);
  destroyList(&h);
}
