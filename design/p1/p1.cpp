/*
 * @Date: 2019-12-20 14:11:57
 * @Author: creedowl
 * @Description: System process statistics
 */
#include <array>
#include <chrono>
#include <iostream>
#include <memory>

#include "linkedList.hpp"

using namespace std;

DoubleLinkedList dl{};
LinkedList list{};

// run command to get system processes
string getProcesses() {
  array<char, 128> buffer;
  string result;
  // use unique pointer to close pipe
  unique_ptr<FILE, decltype(&pclose)> pipe(
      popen("ps --no-headers -ewwo user,pid,%cpu,%mem,stat,etimes,cmd", "r"),
      pclose);
  if (!pipe) {
    throw runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

int main() {
  auto start = chrono::system_clock().now(), end = start;
  while (true) {
    end = chrono::system_clock().now();
    // excute command every second
    if (chrono::duration_cast<chrono::milliseconds>(end - start).count() >
        1000) {
      dl.update(getProcesses(), list);
      system("clear");
      // active processes
      cout << dl << endl;
      cout << endl;
      // finished processes
      cout << list << endl;
      start = chrono::system_clock().now();
    }
  }
}