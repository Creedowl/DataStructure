/*
 * @Date: 2019-10-21 13:26:30
 * @Author: creedowl
 * @Description: e3p4 (csp)
 */
#include <algorithm>
#include <iostream>
using namespace std;

int a[1001], n;

int main() {
  cin >> n;
  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n);
  int mid = n / 2;
  int pre = mid, next = mid;
  while (pre >= 0 and a[pre] >= a[mid]) pre--;
  while (next < n and a[next] <= a[mid]) next++;
  if (pre + 1 == n - next) {
    cout << a[mid] << endl;
  } else {
    cout << -1 << endl;
  }
}
