/*
 * @Date: 2019-10-30 17:13:42
 * @Author: creedowl
 * @Description: e4p2, O(n2)
 */
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int row, col;

int main() {
  cin >> row >> col;
  vector<vector<int>> matrix(row, vector<int>(col));
  vector<int> min_row(row), max_col(col);
  bool flag = false;
  for (size_t i = 0; i < row; i++) {
    min_row[i] = numeric_limits<int>::max();
    for (size_t j = 0; j < col; j++) {
      cin >> matrix[i][j];
      // find the minimun number in each row
      min_row[i] = min(min_row[i], matrix[i][j]);
    }
  }
  for (size_t j = 0; j < col; j++) {
    max_col[j] = matrix[0][j];
    // find the maximun in each column
    for (size_t i = 0; i < row; i++) max_col[j] = max(max_col[j], matrix[i][j]);
    for (size_t i = 0; i < row; i++)
      // find the saddle point
      if (min_row[i] == max_col[j]) {
        cout << i << " " << j << " " << max_col[j] << endl;
        flag = true;
      }
  }
  if (!flag) cout << "no saddle point found" << endl;
}
