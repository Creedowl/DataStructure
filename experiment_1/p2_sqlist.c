/*
 * @Date: 2019-09-25 22:14:06
 * @Author: creedowl
 * @Description: problem 2 using sequential list
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

void listReverse(SqList *l) {
  int temp;
  for (int i = 0; i < l->length / 2; i++) {
    temp = l->element[i];
    l->element[i] = l->element[l->length - i - 1];
    l->element[l->length - i - 1] = temp;
  }
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

int main() {
  SqList l;
  int n;
  printf("please input list size\n");
  scanf("%d", &n);
  createList(&l, n);
  printList(&l);
  listReverse(&l);
  printList(&l);
  destroyList(&l);
}
