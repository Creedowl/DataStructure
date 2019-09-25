/*
 * @Date: 2019-09-22 15:07:01
 * @Author: creedowl
 * @Description: Linked List
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

// return whether a list is empty
int listEmpty(listHead h) { return h->value == 0 ? 1 : 0; }

// return the length of a list
int listLength(listHead h) { return h->value; }

// get an element by a given index, 1 <= i <= l->length
status getElem(listHead h, int i, elemType *e) {
  // index out of range
  if (i < 1 || i > h->value) {
    printf("WARNING: index out of range\n");
    return FAIL;
  }
  for (int j = 0; j < i; j++) h = h->next;
  *e = h->value;
  return SUCCESS;
}

// used for function locateElem
int compare(const elemType *a, const elemType *b) { return *a == *b; }

// get the index of element satisfies the given function with param e
int locateElem(listHead h, elemType e,
               int (*compare)(const elemType *, const elemType *)) {
  int length = h->value;
  for (int i = 0; i < length; i++) {
    h = h->next;
    // call the given function
    if (compare(&h->value, &e)) {
      return i + 1;
    }
  }
  return 0;
}

// get current element's prior element
status priorElem(listHead h, elemType cur_e, elemType *pre_e) {
  int pos = locateElem(h, cur_e, &compare);
  // no nodes in list or only one node left
  if (pos == 0 || pos == 1) return FAIL;
  for (int i = 0; i < pos - 1; i++) h = h->next;
  *pre_e = h->value;
  return SUCCESS;
}

// get current element's next element
status nextElem(listHead h, elemType cur_e, elemType *next_e) {
  int pos = locateElem(h, cur_e, &compare);
  // no nodes in list or current node is the last node
  if (pos == 0 || pos == h->value) return FAIL;
  for (int i = 0; i < pos + 1; i++) h = h->next;
  *next_e = h->value;
  return SUCCESS;
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

// delete an element from a list
status listDelete(listHead h, int i, elemType *e) {
  // index out of range
  if (i < 1 || i > h->value + 1) {
    printf("WARNING: can't delete element, index out of range\n");
    return FAIL;
  }
  // move pointer from head to pos i
  for (int j = 0; j < i - 1; j++) h = h->next;
  // save the pointer to the node to be deleted
  listNode *old = h->next;
  // link to the next node
  h->next = old->next;
  *e = old->value;
  // delete node
  free(old);
  return SUCCESS;
}

// used for function listTraverse
int visit(const elemType *e) {
  printf("%d\n", *e);
  return 1;
}

status listTraverse(listHead h, int (*visit)(const elemType *)) {
  for (h = h->next; h != NULL; h = h->next) {
    if (!visit(&h->value)) return 0;
  }
  return 1;
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

int main() {
  // test all functions
  listHead linkList;
  elemType a;
  // init linked list
  initList(&linkList);
  // test listInsert
  listInsert(linkList, 1, 111);
  listInsert(linkList, 1, 222);
  listInsert(linkList, 2, 333);
  printList(linkList);
  // test listTraverse
  listTraverse(linkList, &visit);
  // test listEmpty
  printf("listEmpty: %d\n", listEmpty(linkList));
  // test listLength
  printf("listLength: %d\n", listLength(linkList));
  // test getElem
  getElem(linkList, 2, &a);
  printf("pos 2 is %d\n", a);
  // test locateElem
  printf("element 111's pos is: %d\n", locateElem(linkList, 111, &compare));
  // test priorElem
  priorElem(linkList, 333, &a);
  printf("element 333's prior element is %d:\n", a);
  // test nextElem
  nextElem(linkList, 333, &a);
  printf("element 333's next element is %d:\n", a);
  // test listDelete
  listDelete(linkList, 2, &a);
  printf("delete element %d\n", a);
  printList(linkList);
  // test destroy list
  destroyList(&linkList);
  // test createList
  createList(&linkList, 5);
  printList(linkList);
  // test clearList
  clearList(linkList);
  printList(linkList);
  free(linkList);
}
