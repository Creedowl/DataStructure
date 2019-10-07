/*
 * @Date: 2019-10-06 17:02:28
 * @Author: creedowl
 * @Description: problem 2 using linked list
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int elemType;

typedef enum { SUCCESS, FAIL } status;

typedef struct LNode {
  elemType value;
  struct LNode *next;
} listNode, *listHead;

// initialize a sequential list
status initList(listHead *h) {
  // h is listHead's pointer that *h is head node
  *h = (listHead)malloc(sizeof(listNode));
  // memory limit exceeded
  if (!(*h)) {
    printf("FATAL: can't create list, memory limit exceeded\n");
    return FAIL;
  }
  // head node's value represents list's length
  (*h)->value = 0;
  (*h)->next = NULL;
  return SUCCESS;
}

// create a linked list by inputting elemType values
status createList(listHead *h, int length) {
  initList(h);
  elemType temp;
  // save head's pointer to update list length
  listHead pos = *h;
  for (int i = 0; i < length; i++) {
    scanf("%d", &temp);
    pos->next = (listNode *)malloc(sizeof(listNode));
    // memory limit exceeded
    if (!pos->next) {
      printf("FATAL: can't create list, memory limit exceeded\n");
      return FAIL;
    }
    // move pointer to the new node
    pos = pos->next;
    pos->value = temp;
    pos->next = NULL;
    (*h)->value++;
  }
  return SUCCESS;
}

// free all nodes and reset head to clear list
void clearList(listHead h) {
  listNode *temp, *pos = h->next;
  while (pos) {
    temp = pos->next;
    free(pos);
    pos = temp;
  }
  h->value = 0;
  h->next = NULL;
}

// free all nodes to destroy a list
void destroyList(listHead *h) {
  clearList(*h);
  free(*h);
}

// inert an element into a list
status listInsert(listHead h, int i, elemType e) {
  // index out of range
  if (i < 1 || i > h->value + 1) {
    printf("WARNING: can't insert element, index out of range\n");
    return FAIL;
  }
  // create new node
  listNode *node = (listNode *)malloc(sizeof(listNode));
  // memory limit exceeded
  if (!node) {
    printf("FATAL: can't create list, memory limit exceeded\n");
    return FAIL;
  }
  // increase list's length
  h->value++;
  node->value = e;
  // move pointer from head to pos i
  for (int j = 0; j < i - 1; j++) h = h->next;
  // save next node's pointer
  node->next = h->next;
  // insert new node
  h->next = node;
  return SUCCESS;
}

// print a list's properties
void printList(listHead h) {
  printf("-----\n");
  printf("length: %d\n", h->value);
  for (h = h->next; h != NULL; h = h->next) {
    printf("%d ", h->value);
  }
  printf("\n------\n");
}

void mergeList(listHead h1, listHead h2) {
  // p1 and p2 represent current node
  listNode *p1 = h1, *p2 = h2;
  // pos is the index of p1 used for insert element
  int pos = 0;
  while (p1->next != NULL || p2->next != NULL) {
    if (p1->next == NULL) {
      // list 1 is empty and attach the rest of list 2 directly
      listInsert(h1, ++pos, p2->next->value);
      p1 = p1->next;
      p2 = p2->next;
    } else if (p2->next == NULL) {
      /** all elements in list 2 is merged into list 1 that means the merge
       * finished
       */
      break;
    } else if (p1->next->value < p2->next->value) {
      /** current element in list 1 is less than the element in list 2,
       *  so move to the next element
       */
      p1 = p1->next;
      pos++;
    } else if (p2->next->value < p1->next->value) {
      /** current element in list 2 is less than the element in list 1,
       *  then merge the smaller one into list 1
       */
      listInsert(h1, ++pos, p2->next->value);
      p1 = p1->next;
      p2 = p2->next;
    } else {
      // skip if two elements are the same
      pos++;
      p1 = p1->next;
      p2 = p2->next;
    }
  }
}

int main() {
  listHead l1, l2;
  createList(&l1, 5);
  createList(&l2, 4);
  mergeList(l1, l2);
  printList(l1);
  destroyList(&l1);
  destroyList(&l2);
}
