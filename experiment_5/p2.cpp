/*
 * @Date: 2019-11-09 17:03:34
 * @Author: creedowl
 * @Description: e5p2 (csp)
 */
#include <iostream>

using namespace std;

int m, n;
int map[30][30], ans[30][30];

int main() {
  cin >> n >> m;
  int temp;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> temp;
      map[i][j] = ans[i][j] = temp;
    }
  }

  if (n >= 3) {
    int head = 0, tail = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (j < m - 1 and map[i][j] == map[i][j + 1]) {
          tail++;
        } else {
          if (tail - head >= 2) {
            for (int k = head; k <= tail; k++) ans[i][k] = 0;
          }
          head = tail = j + 1;
        }
      }
      head = tail = 0;
    }
  }

  if (m >= 3) {
    int head = 0, tail = 0;
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) {
        if (i < n - 1 and map[i][j] == map[i + 1][j]) {
          tail++;
        } else {
          if (tail - head >= 2) {
            for (int k = head; k <= tail; k++) ans[k][j] = 0;
          }
          head = tail = i + 1;
        }
      }
      head = tail = 0;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }
}