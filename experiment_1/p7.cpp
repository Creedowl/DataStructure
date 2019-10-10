/*
 * @Date: 2019-10-10 14:44:46
 * @Author: creedowl
 * @Description: e1p7, O(n)
 */
#include <iostream>
using namespace std;

int main() {
  int pn = 0, n, x0, ai, pow = 1;
  cin >> n >> x0;
  for (int i = 0; i <= n; i++) {
    cin >> ai;
    pow = i == 0 ? 1 : pow * x0;
    pn += ai * pow;
  }
  cout << pn << endl;
}
