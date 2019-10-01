/*
 * @Date: 2019-09-28 21:51:28
 * @Author: creedowl
 * @Description: problem 3 using sequential list
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
  for (int i = 0; i < length; i++) {
    l->element[i] = i + 1;
  }
  return 0;
}

// free l->element to destroy a list
void destroyList(SqList *l) {
  free(l->element);
  l->capacity = 0;
  l->length = 0;
}

void solve(SqList *l, int m) {
  int count = 0, pos = -1, temp = 0;
  while (count < l->length) {
    while (temp < m) {
      pos = (pos + 1) % l->length;
      if (l->element[pos] != -1) temp++;
    }
    printf("%d ", l->element[pos]);
    l->element[pos] = -1;
    temp = 0;
    count++;
  }
  printf("\n");
}

int main() {
  SqList l;
  int m, n;
  scanf("%d%d", &n, &m);
  if (m >= n) {
    printf("FATAL: m must less than n!");
    exit(1);
  }
  createList(&l, n);
  solve(&l, m);
  destroyList(&l);
}
