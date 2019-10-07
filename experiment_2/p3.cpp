/*
 * @Date: 2019-10-07 00:22:51
 * @Author: creedowl
 * @Description: e2p3 (csp)
 */
#include <iostream>
using namespace std;

int main() {
  int n, count = 0, pre, cur, delta = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    pre = cur;
    cin >> cur;
    if (i == 0) continue;
    if ((delta < 0 && cur - pre > 0) || (delta > 0 && cur - pre < 0)) {
      count++;
    }
    delta = cur - pre;
  }
  cout << count << endl;
}