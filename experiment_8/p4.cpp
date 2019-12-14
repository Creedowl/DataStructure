/*
 * @Date: 2019-12-13 15:17:49
 * @Author: creedowl
 * @Description: heap sort
 */
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void heapSort(vector<int> &num) {
  auto adjust = [&](int begin, int end) -> void {
    int left = begin * 2 + 1, right = begin * 2 + 2;
    int pos = begin, ma{0};
    while (left <= end) {
      ma = right <= end and num[right] > num[left] ? right : left;
      if (num[pos] >= num[ma])
        return;
      else {
        swap(num[pos], num[ma]);
        pos = ma;
        left = pos * 2 + 1;
        right = pos * 2 + 2;
      }
    }
  };
  for (int i = num.size() / 2 - 1; i >= 0; i--) {
    adjust(i, num.size() - 1);
  }
  for (int i = num.size() - 1; i > 0; i--) {
    swap(num[0], num[i]);
    adjust(0, i - 1);
  }
}

int main() {
  random_device rd;
  uniform_int_distribution<int> u(0, 100);
  vector<int> num(11);
  for (auto &i : num) i = u(rd);
  for (auto &i : num) cout << i << " ";
  cout << endl;
  heapSort(num);
  for (auto &i : num) cout << i << " ";
  cout << endl;
}
