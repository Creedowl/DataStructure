/*
 * @Date: 2019-10-17 22:46:14
 * @Author: creedowl
 * @Description: e2p6, O(n)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_INITIAL_LENGTH 128
#define LIST_INCREMENT 16

typedef int elemType;

typedef struct {
  elemType *element;
  int length;
  int capacity;
} SqList;

// initialize a sequential list
int initList(SqList *l) {
  l->element = (elemType *)malloc(LIST_INITIAL_LENGTH * sizeof(elemType));
  // memory limit exceeded
  if (!l->element) {
    printf("FATAL: can't create list, memory limit exceeded\n");
    return 0;
  }
  l->capacity = LIST_INITIAL_LENGTH;
  l->length = 0;
  return 1;
}

// create a sequential list by inputting elemType values
int createList(SqList *l, int length) {
  l->element = (elemType *)malloc(length * sizeof(elemType));
  // memory limit exceeded
  if (!l->element) {
    printf("FATAL: can't create list, memory limit exceeded\n");
    return 1;
  }
  l->capacity = length;
  l->length = length;
  printf("please input %d elements: ", length);
  elemType temp;
  for (int i = 0; i < length; i++) {
    scanf("%d", &temp);
    l->element[i] = temp;
  }
  return 0;
}

// free l->element to destroy a list
void destroyList(SqList *l) {
  free(l->element);
  l->capacity = 0;
  l->length = 0;
}

// print a list's properties
void printList(const SqList *l) {
  printf("------\n");
  printf("length: %d\n", l->length);
  printf("capacity: %d\n", l->capacity);
  for (int i = 0; i < l->length; i++) {
    printf("%d ", l->element[i]);
  }
  printf("\n------\n");
}

void solve(SqList *a, const SqList *b, const SqList *c) {
  int p1 = 0, p2 = 0, p3 = 0;
  while (p1 < a->length && p2 < b->length && p3 < c->length) {
    if (b->element[p2] == c->element[p3]) {
      while (p1 < a->length) {
        if (a->element[p1] == b->element[p2]) {
          memmove(a->element + p1, a->element + p1 + 1,
                  (a->length - p1 - 1) * sizeof(elemType));
          a->length--;
          break;
        }
        p1++;
      }
      p2++;
      p3++;
    } else if (b->element[p2] < c->element[p3]) {
      p2++;
    } else {
      p3++;
    }
  }
}

int main() {
  SqList a, b, c;
  createList(&a, 5);
  createList(&b, 4);
  createList(&c, 3);
  solve(&a, &b, &c);
  printList(&a);
  destroyList(&a);
  destroyList(&b);
  destroyList(&c);
}
