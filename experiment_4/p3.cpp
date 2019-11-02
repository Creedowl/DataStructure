/*
 * @Date: 2019-10-30 15:59:30
 * @Author: creedowl
 * @Description: e4p3 (csp)
 */
#include <iostream>

using namespace std;

int n, pos, total = 0;
bool num[10001] = {false};

int main() {
  cin >> n;
  for (size_t i = 0; i < n; i++) {
    cin >> pos;
    if (num[pos]) continue;
    if (num[pos - 1]) total++;
    if (num[pos + 1]) total++;
    num[pos] = true;
  }
  cout << total << endl;
}
