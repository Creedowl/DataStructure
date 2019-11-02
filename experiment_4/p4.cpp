/*
 * @Date: 2019-10-30 16:16:46
 * @Author: creedowl
 * @Description: e4p4 (csp)
 */
#include <iostream>

using namespace std;

int n, num;
int seats[20];

void check(int num, bool newline = true) {
  for (size_t j = 0; j < 20; j++) {
    if (num > 5 - seats[j]) continue;
    for (size_t k = 1; k <= num; k++) cout << j * 5 + seats[j] + k << " ";
    if (newline) cout << endl;
    seats[j] += num;
    return;
  }
  // no continuous seats left
  for (size_t i = 0; i < num; i++) check(1, false);
  cout << endl;
}

int main() {
  cin >> n;
  for (size_t i = 0; i < n; i++) {
    cin >> num;
    check(num);
  }
}
