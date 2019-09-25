/*
 * @Date: 2019-09-21 13:55:49
 * @Author: creedowl
 * @Description: Sequential List
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

// set l->length to 0 to clear a list
void clearList(SqList *l) { l->length = 0; }

// return whether a list is empty
int listEmpty(const SqList *l) { return l->length == 0 ? 1 : 0; }

// return the length of a list
int listLength(const SqList *l) { return l->length; }

// get an element by a given index, 1 <= i <= l->length
int getElem(const SqList *l, int i, elemType *e) {
  if (i < 1 || i > l->length) {
    printf("WARNING: index out of range\n");
    return 0;
  }
  *e = l->element[i - 1];
  return 1;
}

// used for function locateElem
int compare(const elemType *a, const elemType *b) { return *a == *b; }

// get the index of element satisfies the given function with param e
int locateElem(const SqList *l, elemType e,
               int (*compare)(const elemType *, const elemType *)) {
  for (int i = 0; i < l->length; i++) {
    // call the given function
    if (compare(&l->element[i], &e)) {
      return i + 1;
    }
  }
  return 0;
}

// get current element's prior element
int priorElem(const SqList *l, elemType cur_e, elemType *pre_e) {
  int pos = locateElem(l, cur_e, &compare);
  if (pos == 0 || pos == 1) return 0;
  *pre_e = l->element[pos - 2];
  return 1;
}

// get current element's next element
int nextElem(const SqList *l, elemType cur_e, elemType *next_e) {
  int pos = locateElem(l, cur_e, &compare);
  if (pos == 0 || pos == l->length) return 0;
  *next_e = l->element[pos];
  return 1;
}

// inert an element into a list
int listInsert(SqList *l, int i, elemType e) {
  if (i < 1 || i > l->length + 1) {
    printf("WARNING: can't insert element, index out of range\n");
    return 0;
  }
  // extend the list in case of it is full
  if (l->length >= l->capacity) {
    elemType *new;
    new = (elemType *)realloc(
        l->element, (LIST_INCREMENT + l->capacity) * sizeof(elemType));
    // memory limit exceeded
    if (!new) {
      printf("ERROR: no enough memory\n");
      return 0;
    }
    l->element = new;
    l->capacity += LIST_INCREMENT;
  }
  // move the rest elements backward to insert new element
  memmove(l->element + i, l->element + i - 1,
          (l->length - i + 1) * sizeof(elemType));
  l->element[i - 1] = e;
  l->length++;
  return 1;
}

// delete an element from a list
int listDelete(SqList *l, int i, elemType *e) {
  if (i < 1 || i > l->length + 1) {
    printf("WARNING: can't delete element, index out of range\n");
    return 0;
  }
  *e = l->element[i - 1];
  // move the rest elements frontward to delete the element
  memmove(l->element + i - 1, l->element + i,
          (l->length - i) * sizeof(elemType));
  l->length--;
  return 1;
}

// used for function listTraverse
int visit(const elemType *e) {
  printf("%d\n", *e);
  return 1;
}

// use the given function to traverse a list
int listTraverse(const SqList *l, int (*visit)(const elemType *)) {
  for (int i = 0; i < l->length; i++) {
    // call the given function
    if (!visit(&l->element[i])) return 0;
  }
  return 1;
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
  // test all functions
  SqList l;
  initList(&l);
  printf("list empty: %d\n", listEmpty(&l));
  listInsert(&l, 1, 1);
  listInsert(&l, 2, 2);
  listInsert(&l, 3, 3);
  printf("list empty: %d\n", listEmpty(&l));
  printf("list length: %d\n", listLength(&l));
  printList(&l);
  printf("clear list\n");
  clearList(&l);
  printList(&l);
  listInsert(&l, 1, 1);
  printList(&l);
  printf("destroy list\n");
  destroyList(&l);
  createList(&l, 5);
  printList(&l);
  elemType e;
  getElem(&l, 2, &e);
  printf("get element[2]: %d\n", e);
  int i;
  listDelete(&l, 2, &i);
  printf("delete element 2's index: %d\n", i);
  printList(&l);
  printf("locate element 4's index: %d\n", locateElem(&l, 4, &compare));
  priorElem(&l, 3, &e);
  printf("element 3's prior element is: %d\n", e);
  nextElem(&l, 3, &e);
  printf("element 3's next element is: %d\n", e);
  listTraverse(&l, &visit);
  destroyList(&l);
}