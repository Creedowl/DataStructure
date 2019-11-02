/*
 * @Date: 2019-11-01 23:32:02
 * @Author: creedowl
 * @Description: e4p7 (3.32)
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  int data;
} Node;

// init a queue
void initQueue(Node *n, int k) {
  n->data = 0;
  n->next = NULL;
  Node *node, *pos = n;
  for (size_t i = 0; i < k; i++) {
    node = (Node *)malloc(sizeof(Node));
    if (!node) return;
    node->data = 0;
    node->next = NULL;
    pos->next = node;
    pos = pos->next;
    n->data++;
  }
  pos->next = n->next;
}

Node *at(Node *n, int pos) {
  Node *cur = n->next;
  for (size_t i = 0; i < pos; i++) cur = cur->next;
  return cur;
}

void printQueue(const Node *n) {
  if (!n->next) return;
  Node *pos = n->next;
  for (size_t i = 0; i < n->data; i++) {
    printf("%d ", pos->data);
    pos = pos->next;
  }
  printf("\n");
}

int main() {
  Node queue;
  int k, ma, cur = 1, pos = 2;
  scanf("%d%d", &k, &ma);
  initQueue(&queue, k);
  at(&queue, 0)->data = 1;
  at(&queue, 1)->data = 1;
  while (cur < ma) {
    cur = at(&queue, (pos - 1) % k)->data + at(&queue, (pos - 2) % k)->data;
    at(&queue, pos % k)->data = cur;
    pos++;
  }
  printQueue(&queue);
}
