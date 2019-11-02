/*
 * @Date: 2019-11-01 22:51:13
 * @Author: creedowl
 * @Description: e4p6 (3.28)
 *   Circular Queue with head pointer points to the last element
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  struct Node *next;
  int data;
} Node;

// init a queue
void initQueue(Node *n) {
  n->data = 0;
  n->next = NULL;
}

// push an element to the end of a queue
int push(Node *n, int value) {
  Node *node = (Node *)malloc(sizeof(Node));
  if (!node) return 0;
  node->data = value;
  if (n->data == 0) {
    node->next = node;
    n->next = node;
  } else {
    node->next = n->next->next;
    n->next->next = node;
    n->next = node;
  }
  n->data++;
  return 1;
}

// pop an element from the front of a queue
int pop(Node *n, int *value) {
  if (!n->next) return 0;
  *value = n->next->next->data;
  Node *temp = n->next->next;
  n->next->next = temp->next;
  free(temp);
  n->data--;
  return 1;
}

void destroyQueue(Node *n) {
  Node *pos = n->next, *temp;
  for (size_t i = 0; i < n->data; i++) {
    temp = pos->next;
    free(pos);
    pos = temp;
  }
  n->next = NULL;
  n->data = 0;
}

void printQueue(const Node *n) {
  if (!n->next) return;
  Node *pos = n->next->next;
  for (size_t i = 0; i < n->data; i++) {
    printf("%d ", pos->data);
    pos = pos->next;
  }
  printf("\n");
}

int main() {
  Node queue;
  initQueue(&queue);
  push(&queue, 1);
  push(&queue, 2);
  push(&queue, 3);
  printQueue(&queue);
  int data;
  pop(&queue, &data);
  printf("%d\n", data);
  printQueue(&queue);
  destroyQueue(&queue);
}
