/*
 * @Date: 2019-10-13 15:19:22
 * @Author: creedowl
 * @Description: Queue using linked list
 */
#include <stdio.h>
#include <stdlib.h>

typedef int elemType;

typedef enum {
  SUCCESS,
  OutOfMemoryError,
  QueueEmptyError,
  QueueTraverseError
} status;

typedef struct qNode {
  elemType value;
  struct qNode *next;
} qNode;

typedef struct {
  qNode *front, *rear;
  int length;
} Queue;

// initialize a Queue
status initQueue(Queue *q) {
  qNode *node = (qNode *)malloc(sizeof(qNode));
  if (!node) {
    printf("FATAL: can't create stack, memory limit exceeded\n");
    return OutOfMemoryError;
  }
  node->next = NULL;
  q->front = node;
  q->rear = node;
  q->length = 0;
  return SUCCESS;
}

/* free all nodes except q->front and
 * reset attributes to destroy a Queue
 */
void clearQueue(Queue *q) {
  qNode *temp, *pos = q->front->next;
  while (pos != NULL) {
    temp = pos->next;
    free(pos);
    pos = temp;
  }
  q->front->next = NULL;
  q->rear = q->front;
  q->length = 0;
}

// ree all nodes to destroy a Queue
void destroyQueue(Queue *q) {
  clearQueue(q);
  free(q->front);
}

// return whether a Queue is empty
int queueEmpty(const Queue *q) { return q->length == 0 ? 1 : 0; }

// return the length of a Queue
int queueLength(const Queue *q) { return q->length; }

// get the head element of a Queue
status getHead(const Queue *q, elemType *e) {
  if (q->length <= 0) return QueueEmptyError;
  *e = q->front->next->value;
  return SUCCESS;
}

// push an element to the rear of a Queue
status push(Queue *q, elemType e) {
  qNode *node = (qNode *)malloc(sizeof(qNode));
  if (!node) {
    printf("FATAL: can't create stack, memory limit exceeded\n");
    return OutOfMemoryError;
  }
  node->value = e;
  node->next = NULL;
  q->rear->next = node;
  q->rear = q->rear->next;
  q->length++;
  return SUCCESS;
}

// pop an element from the front of a Queue
status pop(Queue *q, elemType *e) {
  if (q->length <= 0) return QueueEmptyError;
  *e = q->front->next->value;
  qNode *temp = q->front->next;
  q->front->next = temp->next;
  free(temp);
  q->length--;
  return SUCCESS;
}

// used for function queueTraverse
int visit(const elemType *e) {
  printf("%d\n", *e);
  return 1;
}

// use the given function to traverse a queue
status queueTraverse(const Queue *q, int (*visit)(const elemType *)) {
  for (qNode *pos = q->front->next; pos != NULL; pos = pos->next) {
    if (!visit(&pos->value)) return QueueTraverseError;
  }
  return SUCCESS;
}

// alias to function push
status enQueue(Queue *q, elemType e) { return push(q, e); }

// alias to function pop
status deQueue(Queue *q, elemType *e) { return pop(q, e); }

void printQueue(const Queue *q) {
  printf("------\n");
  printf("length: %d\n", q->length);

  for (qNode *pos = q->front->next; pos != NULL; pos = pos->next)
    printf("%d ", pos->value);
  printf("\n------\n");
}

int main() {
  Queue q;
  initQueue(&q);
  push(&q, 1);
  push(&q, 2);
  push(&q, 3);
  printQueue(&q);
  printf("queue lenght: %d\n", queueLength(&q));
  elemType e;
  pop(&q, &e);
  printQueue(&q);
  getHead(&q, &e);
  printf("get head element: %d\n", e);
  queueTraverse(&q, &visit);
  pop(&q, &e);
  printQueue(&q);
  destroyQueue(&q);
}
