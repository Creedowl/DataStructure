/*
 * @Date: 2020-01-01 20:02:56
 * @Author: creedowl
 * @Description: sort algorithm
 */
#include <algorithm>
#include <chrono>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
using namespace chrono;

vector<int> nums(50000);

// call sort function in algorithm
void standerSort(vector<int> list) { sort(list.begin(), list.end()); }

void insertionSort(vector<int> list) {
  int cur{0};
  for (size_t i = 1; i < list.size(); i++) {
    cur = list[i];
    int j = i - 1;
    while (j >= 0 and cur < list[j]) {
      list[j + 1] = list[j];
      j--;
    }
    list[j + 1] = cur;
  }
}

void bubbleSort(vector<int> list) {
  int temp{0};
  for (size_t i = 1; i < list.size(); i++) {
    for (size_t j = 0; j < list.size() - i; j++) {
      if (list[j] > list[j + 1]) {
        temp = list[j];
        list[j] = list[j + 1];
        list[j + 1] = temp;
      }
    }
  }
}

void selectionSort(vector<int> list) {
  int temp{0};
  for (size_t i = 0; i < list.size(); i++) {
    int mi{numeric_limits<int>::max()};
    int pos{0};
    for (size_t j = i; j < list.size(); j++) {
      if (list[j] < mi) {
        pos = j;
        mi = list[j];
      }
    }
    temp = list[i];
    list[i] = list[pos];
    list[pos] = temp;
  }
}

void mergeSort(vector<int> list) {
  vector<int> temp(list.size());
  for (size_t i = 1; i < list.size(); i *= 2) {
    for (size_t j = 0; j < list.size(); j += i * 2) {
      int h1 = j, h2 = j + i, pos = 0;
      int e1 = min(j + i, list.size()), e2 = min(j + i * 2, list.size());
      while (h1 < e1 or h2 < e2) {
        if (h1 >= e1)
          temp[pos++] = list[h2++];
        else if (h2 >= e2)
          temp[pos++] = list[h1++];
        else if (list[h1] < list[h2])
          temp[pos++] = list[h1++];
        else if (list[h1] >= list[h2])
          temp[pos++] = list[h2++];
      }
      for (size_t k = j, p = 0; k < e2; k++, p++) {
        list[k] = temp[p];
      }
    }
  }
}

void _quickSort(vector<int> &list, int begin, int end) {
  if (begin >= end) return;
  int pos{begin + 1};
  for (size_t i = begin + 1; i <= end; i++) {
    if (list[i] < list[begin]) swap(list[i], list[pos++]);
  }
  swap(list[begin], list[pos - 1]);
  _quickSort(list, begin, pos - 2);
  _quickSort(list, pos, end);
}

void quickSort(vector<int> list) { _quickSort(list, 0, list.size() - 1); }

void heapSort(vector<int> list) {
  auto adjust = [&](int begin, int end) -> void {
    int left = begin * 2 + 1, right = begin * 2 + 2;
    int pos = begin, ma{0};
    while (left <= end) {
      ma = right <= end and list[right] > list[left] ? right : left;
      if (list[pos] >= list[ma])
        return;
      else {
        swap(list[pos], list[ma]);
        pos = ma;
        left = pos * 2 + 1;
        right = pos * 2 + 2;
      }
    }
  };
  for (int i = list.size() / 2 - 1; i >= 0; i--) {
    adjust(i, list.size() - 1);
  }
  for (int i = list.size() - 1; i > 0; i--) {
    swap(list[0], list[i]);
    adjust(0, i - 1);
  }
}

void shellSort(vector<int> list) {
  for (int delta = list.size() / 2; delta > 0; delta /= 2)
    for (int i = delta; i < list.size(); i++)
      for (int j = i; j >= delta and list[j] < list[j - delta]; j -= delta)
        swap(list[j], list[j - delta]);
}

void radixSort(vector<int> list) {
  vector<vector<int>> collect(10);
  int ma{0}, bit{0}, level{1};
  for (auto &i : list) ma = max(ma, i);
  while (ma) {
    bit++;
    ma /= 10;
  }
  for (size_t i = 0; i < bit; i++) {
    for (auto &j : list) collect[(j / level) % 10].push_back(j);
    level *= 10;
    list.clear();
    for (auto &j : collect) {
      for (auto &k : j) list.push_back(k);
      j.clear();
    }
  }
}

void test(vector<int> &list, string func_name,
          const function<void(vector<int>)> sort_func) {
  auto begin = system_clock::now();
  sort_func(list);
  cout << func_name << " costs "
       << duration_cast<microseconds>(system_clock::now() - begin).count()
       << " micro seconds" << endl;
}

int main() {
  for (int i = 1; i <= 10; i++) {
    char file_name[20] = {0};
    sprintf(file_name, "data%d.in", i);
    fstream f(file_name, ios::in);
    for (size_t j = 0; j < 50000; j++) f >> nums[j];
    f.close();
    cout << "testing " << file_name << endl;
    test(nums, "stander sort", standerSort);
    test(nums, "insertion sort", insertionSort);
    test(nums, "bubble sort", bubbleSort);
    test(nums, "selection sort", selectionSort);
    test(nums, "merge sort", mergeSort);
    test(nums, "quick sort", quickSort);
    test(nums, "heap sort", heapSort);
    test(nums, "shell sort", shellSort);
    test(nums, "radix sort", radixSort);
  }
}
