/*
 * @Date: 2019-10-01 16:17:52
 * @Author: creedowl
 * @Description: problem 5 (csp)
 */
#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

static int _ = []() {
  std::iostream::sync_with_stdio(false);
  std::cin.tie(0);
  return 0;
}();

int main() {
  int n, m, p, q;
  cin >> n >> m;
  list<int> students;
  for (int i = 0; i < n; i++) students.push_back(i + 1);
  for (int i = 0; i < m; i++) {
    cin >> p >> q;
    auto it = find(students.cbegin(), students.cend(), p);
    auto temp = it;
    temp++;
    students.erase(it);
    advance(temp, q);
    students.insert(temp, p);
  }
  for (int i : students) {
    cout << i << " ";
  }
  cout << endl;
}
