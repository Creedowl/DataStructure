/*
 * @Date: 2020-01-01 15:54:18
 * @Author: creedowl
 * @Description: generate ramdon
 */
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

int main() {
  random_device rd;
  uniform_int_distribution<int> u(0, 5000);
  fstream f1("data1.in", ios::out);
  fstream f2("data2.in", ios::out);
  for (size_t i = 0; i < 50000; i++) {
    f1 << i << " ";
    f2 << 50000 - i << " ";
  }
  f1.close();
  f2.close();

  for (int i = 3; i <= 10; i++) {
    char file_name[20];
    sprintf(file_name, "data%d.in", i);
    fstream f(file_name, ios::out);
    for (size_t j = 0; j < 50000; j++) f << u(rd) << " ";
    f.close();
  }
}
