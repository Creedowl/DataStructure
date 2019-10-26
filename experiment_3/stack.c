/*
 * @Date: 2019-10-10 21:05:11
 * @Author: creedowl
 * @Description: stack using sequential list
 */
#include <stdio.h>
#include <stdlib.h>

#define STACK_INITIAL_LENGTH 128
#define STACK_INCREMENT 16

typedef enum {
  SUCCESS,
  OutOfMemoryError,
  DoubleFreeError,
  StackEmptyError,
  StackTraverseError
} status;

typedef int elemType;

typedef struct {
  elemType *elemSet;
  int length;
  int capacity;
} Stack;

// initialize a stack
status initStack(Stack *s) {
  s->elemSet = (elemType *)malloc(STACK_INITIAL_LENGTH * sizeof(elemType));
  if (!s->elemSet) {
    printf("FATAL: can't create stack, memory limit exceeded\n");
    return OutOfMemoryError;
  }
  s->length = 0;
  s->capacity = STACK_INITIAL_LENGTH;
  return SUCCESS;
}

// free s->elemSet to destroy a stack
status destroyStack(Stack *s) {
  if (!s->elemSet) return DoubleFreeError;
  free(s->elemSet);
  s->length = 0;
  s->capacity = 0;
  return SUCCESS;
}

// set l->length to 0 to clear a stack
void clearStack(Stack *s) { s->length = 0; }

// return whether a stack is empty
int stackEmpty(const Stack *s) { return s->length == 0 ? 1 : 0; }

// return the length of a stack
int stackLength(const Stack *s) { return s->length; }

// get the top element in a stack
void getTop(const Stack *s, elemType *e) { *e = s->elemSet[s->length - 1]; }

// push an element to the end of a stack
status push(Stack *s, elemType e) {
  // extend the stack in case of it is full
  if (s->length >= s->capacity) {
    elemType *new = (elemType *)realloc(
        s->elemSet, (STACK_INCREMENT + s->capacity) * sizeof(elemType));
    // memory limit exceeded
    if (!new) {
      printf("ERROR: no enough memory\n");
      return OutOfMemoryError;
    }
    s->capacity += STACK_INCREMENT;
  }
  s->elemSet[s->length] = e;
  s->length++;
  return SUCCESS;
}

// pop out the last element in a stack
status pop(Stack *s, elemType *e) {
  if (s->length <= 0) {
    printf("WARNING: stack is empty!\n");
    return StackEmptyError;
  }
  *e = s->elemSet[s->length - 1];
  s->length--;
  return SUCCESS;
}

// used for function stackTraverse
int visit(const elemType *e) {
  printf("%d\n", *e);
  return 1;
}

// use the given function to traverse a stack
status stackTraverse(const Stack *s, int (*visit)(const elemType *)) {
  for (int i = 0; i < s->length; i++) {
    if (!visit(&s->elemSet[i])) return StackTraverseError;
  }
  return SUCCESS;
}

void printStack(const Stack *s) {
  printf("------\n");
  printf("length: %d\n", s->length);
  printf("capacity: %d\n", s->capacity);
  for (int i = 0; i < s->length; i++) printf("%d ", s->elemSet[i]);
  printf("\n------\n");
}

int main() {
  Stack s;
  initStack(&s);
  push(&s, 0);
  push(&s, 1);
  push(&s, 2);
  printStack(&s);
  printf("stack empty: %d\n", stackEmpty(&s));
  printf("stack length: %d\n", stackLength(&s));
  elemType e;
  getTop(&s, &e);
  printf("top element in the stack: %d\n", e);
  pop(&s, &e);
  printf("pop the top element in the stack: %d\n", e);
  printStack(&s);
  printf("test stackTraverse\n");
  stackTraverse(&s, &visit);
  clearStack(&s);
  printStack(&s);
  destroyStack(&s);
}
