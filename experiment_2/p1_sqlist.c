/*
 * @Date: 2019-10-05 15:57:11
 * @Author: creedowl
 * @Description: Selection sort using sequential list
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

/** using selection sort to sort list, type is sort order,
 *  1 represents ascending order and 0 represents descending order
 */
void sortList(SqList *l, int type) {
  int pos, temp;
  for (int i = 0; i < l->length; i++) {
    pos = i;
    for (int j = i; j < l->length; j++) {
      if (l->element[j] < l->element[pos] && type)
        pos = j;
      else if (l->element[j] > l->element[pos] && !type)
        pos = j;
    }
    temp = l->element[i];
    l->element[i] = l->element[pos];
    l->element[pos] = temp;
  }
}

int main() {
  SqList l;
  createList(&l, 5);
  printList(&l);
  sortList(&l, 1);
  printList(&l);
  destroyList(&l);
}
