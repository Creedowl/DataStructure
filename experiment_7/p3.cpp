/*
 * @Date: 2019-12-11 10:17:48
 * @Author: creedowl
 * @Description: e7p3 (csp)
 */
#include <iostream>

using namespace std;

int n;
int map[3][3];

// check all possible solutions
bool check(int v) {
  if (map[0][0] == v and map[0][1] == v and map[0][2] == v) return true;
  if (map[1][0] == v and map[1][1] == v and map[1][2] == v) return true;
  if (map[2][0] == v and map[2][1] == v and map[2][2] == v) return true;
  if (map[0][0] == v and map[1][0] == v and map[2][0] == v) return true;
  if (map[0][1] == v and map[1][1] == v and map[2][1] == v) return true;
  if (map[0][2] == v and map[1][2] == v and map[2][2] == v) return true;
  if (map[0][0] == v and map[1][1] == v and map[2][2] == v) return true;
  if (map[0][2] == v and map[1][1] == v and map[2][0] == v) return true;
  return false;
}

// return blanks in the map
int blank() {
  int blank{0};
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (map[i][j] == 0) blank++;
    }
  }
  return blank;
}

// return scores
int win(int peo) {
  if (check(peo)) return peo == 1 ? blank() + 1 : -(blank() + 1);
  return 0;
}

// traverse all available position
int dfs(int peo) {
  if (blank() == 0) return 0;
  int ans{0}, ma = -5, mi = 5;
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      if (map[i][j] == 0) {
        map[i][j] = peo;
        ans = win(peo);
        if (ans != 0) {
          map[i][j] = 0;
          return ans > 0 ? max(ma, ans) : min(mi, ans);
        }
        if (peo == 1) {
          ma = max(ma, dfs(2));
        } else {
          mi = min(mi, dfs(1));
        }
        map[i][j] = 0;
      }
    }
  }
  return peo == 1 ? ma : mi;
}

int main() {
  cin >> n;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < 3; j++) {
      for (size_t k = 0; k < 3; k++) cin >> map[j][k];
    }
    int r1 = win(1), r2 = win(2);
    if (r1 != 0) {
      cout << r1 << endl;
      continue;
    }
    if (r2 != 0) {
      cout << r2 << endl;
      continue;
    }
    cout << dfs(1) << endl; // Alice-1, Bob-2
  }
}
