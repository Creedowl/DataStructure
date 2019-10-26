/*
 * @Date: 2019-10-19 21:01:32
 * @Author: creedowl
 * @Description: eight queen using stack
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

void show(const Stack *s, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j == s->elemSet[i]) {
        printf("1 ");
      } else {
        printf("0 ");
      }
    }
    printf("\n");
  }
  printf("\n");
}

int check(int x, int y, Stack *s) {
  for (int i = 0; i < s->length; i++) {
    if (y == s->elemSet[i] || x + y == i + s->elemSet[i] ||
        x - y == i - s->elemSet[i])
      return 0;
  }
  return 1;
}

void solve(Stack *s, int n, int *total) {
  int i = 0, j = 0, top = 0;
  while (!(i == 0 && j == n)) {
    if (j >= n) {
      while (j >= n) {
        if (s->length == 0) break;
        pop(s, &j);
        i--;
        j++;
      }
    } else if (check(i, j, s)) {
      push(s, j);
      if (s->length == n) {
        (*total)++;
        show(s, n);
        pop(s, &j);
        pop(s, &j);
        i--;
        j++;
      } else {
        i++;
        j = 0;
      }
    } else {
      j++;
    }
  }
}

int main() {
  int n, total = 0;
  scanf("%d", &n);
  Stack queen;
  initStack(&queen);
  solve(&queen, n, &total);
  printf("%d\n", total);
  destroyStack(&queen);
}
