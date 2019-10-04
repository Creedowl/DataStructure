/*
 * @Date: 2019-10-01 14:56:37
 * @Author: creedowl
 * @Description: problem 4 (csp)
 */
#include <iostream>
using namespace std;

int main() {
  int r, y, g, n, k, t;
  int total = 0;
  cin >> r >> y >> g;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> k >> t;
    switch (k) {
      case 0:
      case 1:
        total += t;
        break;
      case 2:
        total += t + r;
      default:
        break;
    }
  }
  printf("%d\n", total);
}