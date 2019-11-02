/*
 * @Date: 2019-10-26 20:19:20
 * @Author: creedowl
 * @Description: Sparse matrix using c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 128

typedef int elemType;

typedef struct {
  int i, j;
  elemType e;
} Triple;

typedef struct {
  Triple data[MAXSIZE];
  int rowNum, colNum, total;
} Matrix;

// create a sparse matrix
void createMatrix(Matrix *m) {
  printf("please input rowNum, colNum and total elements: ");
  scanf("%d%d%d", &m->rowNum, &m->colNum, &m->total);
  for (size_t p = 0; p < m->total; p++) {
    printf("please input i, j and e: ");
    scanf("%d%d%d", &m->data[p].i, &m->data[p].j, &m->data[p].e);
  }
}

// display the entire matrix
void printMatrix(const Matrix *m) {
  int p = 0;
  for (size_t i = 0; i < m->rowNum; i++) {
    for (size_t j = 0; j < m->colNum; j++) {
      if (i == m->data[p].i && j == m->data[p].j) {
        printf("%d ", m->data[p].e);
        p++;
      } else {
        printf("0 ");
      }
    }
    printf("\n");
  }
}

/**
 * brute force, scan the entire src->data to find the target
 * triple, time complexity is O(n2)
 */
void transposeMatrix(const Matrix *src, Matrix *dest) {
  dest->colNum = src->rowNum;
  dest->rowNum = src->colNum;
  dest->total = src->total;
  int p = 0;
  for (size_t col = 0; col < src->colNum; col++) {
    for (size_t pos = 0; pos < src->total; pos++) {
      if (src->data[pos].j == col) {
        dest->data[p].i = src->data[pos].j;
        dest->data[p].j = src->data[pos].i;
        dest->data[p].e = src->data[pos].e;
        p++;
      }
    }
  }
}

/**
 * fast transpose, calculate where to place a triple in dest
 * from src, time complexity is O(n)
 */
void fastTransposeMatrix(const Matrix *src, Matrix *dest) {
  dest->colNum = src->rowNum;
  dest->rowNum = src->colNum;
  dest->total = src->total;
  // the number of triples in each column
  int num[src->rowNum];
  memset(num, 0, sizeof(num));
  // the position to place a triple from src in dest
  int cpot[src->rowNum];
  memset(cpot, 0, sizeof(cpot));
  int pos;
  // count the number of triples in each column
  for (size_t i = 0; i < src->total; i++) num[src->data[i].j]++;
  cpot[0] = 0;
  // calculate the position of first triple in each column
  for (size_t i = 1; i < src->colNum; i++) cpot[i] = cpot[i - 1] + num[i - 1];
  // transpose matrix
  for (size_t i = 0; i < src->total; i++) {
    pos = cpot[src->data[i].j];
    dest->data[pos].i = src->data[i].j;
    dest->data[pos].j = src->data[i].i;
    dest->data[pos].e = src->data[i].e;
    // place the next triple in the next position
    cpot[src->data[i].j]++;
  }
}

int main() {
  Matrix m, t;
  createMatrix(&m);
  printMatrix(&m);
  transposeMatrix(&m, &t);
  printMatrix(&t);
  fastTransposeMatrix(&m, &t);
  printMatrix(&t);
}
