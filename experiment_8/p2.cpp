/*
 * @Date: 2019-12-12 15:05:45
 * @Author: creedowl
 * @Description: simple sort algorithm
 */
#include <iostream>
#include <limits>
#include <random>
#include <vector>

using namespace std;

void bubbleSort(vector<int> num, bool order = true) {
  int temp{0};
  for (size_t i = 1; i < num.size(); i++) {
    for (size_t j = 0; j < num.size() - i; j++) {
      if (num[j] < num[j + 1] and order) {
        temp = num[j];
        num[j] = num[j + 1];
        num[j + 1] = temp;
      } else if (num[j] > num[j + 1] and !order) {
        temp = num[j];
        num[j] = num[j + 1];
        num[j + 1] = temp;
      }
    }
  }
  for (auto &i : num) cout << i << " ";
  cout << endl;
}

void selectionSort(vector<int> num, bool order = true) {
  int temp{0};
  for (size_t i = 0; i < num.size(); i++) {
    int mi{numeric_limits<int>::max()}, ma{numeric_limits<int>::min()};
    int pos{0};
    for (size_t j = i; j < num.size(); j++) {
      if (order and num[j] > ma) {
        pos = j;
        ma = num[j];
      } else if (!order and num[j] < mi) {
        pos = j;
        mi = num[j];
      }
    }
    temp = num[i];
    num[i] = num[pos];
    num[pos] = temp;
  }
  for (auto &i : num) cout << i << " ";
  cout << endl;
}

void mergeSort(vector<int> num, bool order = true) {
  vector<int> temp(num.size());
  for (size_t i = 1; i < num.size(); i *= 2) {
    for (size_t j = 0; j < num.size(); j += i * 2) {
      int h1 = j, h2 = j + i, pos = 0;
      int e1 = min(j + i, num.size()), e2 = min(j + i * 2, num.size());
      while (h1 < e1 or h2 < e2) {
        if (h1 >= e1)
          temp[pos++] = num[h2++];
        else if (h2 >= e2)
          temp[pos++] = num[h1++];
        else if (order and num[h1] > num[h2])
          temp[pos++] = num[h1++];
        else if (order and num[h1] <= num[h2])
          temp[pos++] = num[h2++];
        else if (!order and num[h1] < num[h2])
          temp[pos++] = num[h1++];
        else if (!order and num[h1] >= num[h2])
          temp[pos++] = num[h2++];
      }
      for (size_t k = j, p = 0; k < e2; k++, p++) {
        num[k] = temp[p];
      }
    }
  }
  for (auto &i : num) cout << i << " ";
  cout << endl;
}

int main() {
  random_device rd;
  uniform_int_distribution<int> u(0, 100);
  vector<int> num(11);
  for (auto &i : num) i = u(rd);
  for (auto &i : num) cout << i << " ";
  cout << endl;
  bubbleSort(num);
  bubbleSort(num, false);
  selectionSort(num);
  selectionSort(num, false);
  mergeSort(num);
  mergeSort(num, false);
}
