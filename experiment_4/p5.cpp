/*
 * @Date: 2019-10-31 08:49:22
 * @Author: creedowl
 * @Description: e4p5 (3.20)
 */
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
  int row, col;
  int x, y, old_color, new_color;
  cin >> row >> col;
  queue<vector<int>> same;
  vector<vector<int>> g(row + 2, vector<int>(col + 2));
  for (size_t i = 1; i <= row; i++) {
    for (size_t j = 1; j <= col; j++) cin >> g[i][j];
  }
  cin >> x >> y >> new_color;
  old_color = g[x + 1][y + 1];
  g[x + 1][y + 1] = new_color;
  same.push({x + 1, y + 1});
  int cur_x, cur_y;
  while (!same.empty()) {
    cur_x = same.front()[0];
    cur_y = same.front()[1];
    same.pop();
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (abs(i) == abs(j)) continue;
        if (g[cur_x + i][cur_y + j] == old_color) {
          g[cur_x + i][cur_y + j] = new_color;
          same.push({cur_x + i, cur_y + j});
        }
      }
    }
  }
  for (size_t i = 1; i <= row; i++) {
    for (size_t j = 1; j <= col; j++) cout << g[i][j] << " ";
    cout << endl;
  }
}
