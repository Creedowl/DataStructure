/*
 * @Date: 2019-10-06 15:01:06
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

void mergeList(SqList *l1, const SqList *l2) {
  int p1 = 0, p2 = 0;
  while (p1 < l1->length || p2 < l2->length) {
    if (p1 >= l1->length) {
      // list 1 is empty and attach the rest of list 2 directly
      listInsert(l1, l1->length + 1, l2->element[p2++]);
    } else if (p2 >= l2->length) {
      /** all elements in list 2 is merged into list 1 that means the merge
       * finished
       */
      break;
    } else if (l1->element[p1] < l2->element[p2]) {
      /** current element in list 1 is less than the element in list 2,
       *  so move to the next element
       */
      p1++;
    } else if (l2->element[p2] < l1->element[p1]) {
      /** current element in list 2 is less than the element in list 1,
       *  then merge the smaller one into list 1
       */
      listInsert(l1, ++p1, l2->element[p2++]);
    } else {
      // skip if two elements are the same
      p1++;
      p2++;
    }
  }
}

int main() {
  SqList l1, l2;
  createList(&l1, 4);
  createList(&l2, 5);
  mergeList(&l1, &l2);
  printList(&l1);
  destroyList(&l1);
  destroyList(&l2);
}
