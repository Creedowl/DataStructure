/*
 * @Date: 2020-01-03 19:48:03
 * @Author: creedowl
 * @Description: csp (201803-1)
 */
#include <iostream>

using namespace std;

int main() {
  int pre{-1}, cur{-1}, sum{0};
  while (cur != 0) {
    cin >> cur;
    if (cur == 0) break;
    if (cur == 1) {
      pre = 1;
      sum += 1;
    } else if (cur == 2) {
      if (pre == 1 or pre == -1) pre = 2;
      sum += pre;
      pre += 2;
    }
  }
  cout << sum << endl;
}
