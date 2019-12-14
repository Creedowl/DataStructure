/*
 * @Date: 2019-12-13 14:27:39
 * @Author: creedowl
 * @Description: quick sort
 */
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void quickSort(vector<int> &num, int begin, int end) {
  if (begin >= end) return;
  int head = begin, tail = end, mid = num[begin];
  while (head < tail) {
    while (head < tail and num[tail] >= mid) tail--;
    num[head] = num[tail];
    while (head < tail and num[head] < mid) head++;
    num[tail] = num[head];
  }
  num[head] = mid;
  quickSort(num, begin, head - 1);
  quickSort(num, head + 1, end);
}

int main() {
  random_device rd;
  uniform_int_distribution<int> u(0, 100);
  vector<int> num(11);
  for (auto &i : num) i = u(rd);
  for (auto &i : num) cout << i << " ";
  cout << endl;
  quickSort(num, 0, num.size() - 1);
  for (auto &i : num) cout << i << " ";
  cout << endl;
}
