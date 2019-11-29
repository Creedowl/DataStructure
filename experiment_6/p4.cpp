/*
 * @Date: 2019-11-27 10:19:59
 * @Author: creedowl
 * @Description: p4 (csp)
 */
#include <algorithm>
#include <iostream>

using namespace std;

int n, l, t;

struct Ball {
  int index{0}, pos{0}, speed{1};
} ball[101];

int main() {
  cin >> n >> l >> t;
  int temp;
  for (size_t i = 0; i < n; i++) {
    cin >> temp;
    ball[i].index = i;
    ball[i].pos = temp;
  }
  sort(ball, ball + n, [](const Ball &b1, const Ball &b2) -> bool {
    return b1.pos < b2.pos;
  });
  for (size_t i = 0; i < t; i++) {
    for (size_t j = 0; j < n; j++) ball[j].pos += ball[j].speed;
    for (size_t j = 0; j < n; j++) {
      if (ball[j].pos == 0 or ball[j].pos == l) ball[j].speed = -ball[j].speed;
      if (j > 0 or j < l) {
        if (ball[j + 1].pos == ball[j].pos) {
          ball[j + 1].speed = -ball[j + 1].speed;
          ball[j].speed = -ball[j].speed;
        }
      }
    }
  }
  sort(ball, ball + n, [](const Ball &b1, const Ball &b2) -> bool {
    return b1.index < b2.index;
  });
  for (size_t i = 0; i < n; i++) cout << ball[i].pos << " ";
  cout << endl;
}
