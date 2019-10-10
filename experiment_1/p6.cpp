/*
 * @Date: 2019-10-09 14:57:47
 * @Author: creedowl
 * @Description: e1p6
 */
#include <climits>
#include <iostream>

#define ARRAY_SIZE 128

using namespace std;

typedef enum { SUCCESS, IndexOutOfRangeError, NumTooLargeError } status;
typedef unsigned long long ull;

ull a[ARRAY_SIZE];
ull fact = 1, pow = 1;

status calc(int n) {
  if (n > ARRAY_SIZE) return IndexOutOfRangeError;

  a[0] = 1;
  cout << a[0] << " ";
  for (int i = 1; i < n; i++) {
    fact *= i;
    pow *= 2;
    if (fact <= 0 || pow <= 0 || fact * pow <= 0) {
      cout << endl;
      return NumTooLargeError;
    }
    a[i] = fact * pow;
    cout << a[i] << " ";
  }
  cout << endl;
  return SUCCESS;
}

int main() {
  int n;
  cin >> n;
  switch (calc(n)) {
    case IndexOutOfRangeError:
      cout << "FATAL: index out of range" << endl;
      break;
    case NumTooLargeError:
      cout << "too large" << endl;
    default:
      break;
  }
}
