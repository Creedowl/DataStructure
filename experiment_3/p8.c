/*
 * @Date: 2019-10-25 23:07:29
 * @Author: creedowl
 * @Description: e3p8 2.38
 */
#include <stdio.h>
#include <stdlib.h>

typedef int elemType;

typedef struct LNode {
  elemType data;
  struct LNode *prior, *next;
  int freq;
} listNode, listHead;

int initList(listHead *h) {
  h->data = 0;
  h->prior = NULL;
  h->next = NULL;
  h->freq = 0;
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
    node->freq = 0;
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
  h->freq = 0;
  h->prior = NULL;
  h->next = NULL;
}

int locate(listHead *h, elemType e) {
  listNode *temp, *pos = h->next;
  for (size_t i = 0; i < h->data; i++) {
    if (pos->data == e) {
      pos->freq++;
      if (pos == h->next) return i;
      temp = pos;
      pos->prior->next = temp->next;
      pos->next->prior = temp->prior;
      pos = pos->prior;
      for (--i; i >= 0; i--) {
        if (pos->freq > temp->freq) {
          temp->next = pos->next;
          temp->prior = pos;
          pos->next->prior = temp;
          pos->next = temp;
          return ++i;
        } else if (i == 0) {
          temp->next = h->next;
          temp->prior = h->next->prior;
          h->next->prior->next = temp;
          h->next->prior = temp;
          h->next = temp;
          return i;
        } else {
          pos = pos->prior;
        }
      }
      break;
    }
    pos = pos->next;
  }
  return -1;
}

void printList(listHead *h) {
  listNode *pos = h->next;
  printf("list size: %d\n", h->data);
  for (size_t i = 0; i < h->data; i++) {
    printf("prior: %d, next: %d, data: %d, freq: %d\n", pos->prior->data,
            pos->next->data, pos->data, pos->freq);
    pos = pos->next;
  }
}

int main() {
  listHead h;
  createList(&h, 5);
  printList(&h);
  int pos;
  pos = locate(&h, 4);
  printf("%d\n", pos);
  pos = locate(&h, 4);
  printf("%d\n", pos);
  pos = locate(&h, 1);
  printf("%d\n", pos);
  pos = locate(&h, 6);
  printf("%d\n", pos);
  printList(&h);
  destroyList(&h);
}
