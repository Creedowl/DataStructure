/*
 * @Date: 2019-12-20 15:14:49
 * @Author: creedowl
 * @Description: double linked list
 */
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

class Node {
public:
  string user;
  int pid;
  double cpu, mem;
  string stat;
  int elapsedTime;
  string command;
  time_t endTime{0};
  Node *pre{nullptr}, *next{nullptr};

  Node() = default;

  Node(string user, int pid, double cpu, double mem, string stat,
       int elapsedTime, string command)
      : user(user),
        pid(pid),
        cpu(cpu),
        mem(mem),
        stat(stat),
        elapsedTime(elapsedTime),
        command(command) {}
};

class LinkedList {
private:
  int size{0};
  Node root{};

public:
  ~LinkedList() {
    Node *p{this->root.next}, *temp{nullptr};
    while (p != nullptr) {
      temp = p->next;
      delete p;
      p = temp;
    }
  }

  // show all finished processes
  friend ostream &operator<<(ostream &os, const LinkedList &list) {
    os << "----- Finished Processes -----" << endl;
    os << left << setw(5) << "PID"
       << " " << setw(10) << "USER"
       << " " << setw(4) << "STAT"
       << " " << setw(9) << "ENDTIME"
       << " "
       << "COMMAND" << endl;
    for (Node *p{list.root.next}; p != nullptr; p = p->next) {
      os << left << setw(5) << p->pid << " " << setw(10) << p->user << " "
         << setw(4) << p->stat << " " << setw(2)
         << put_time(localtime(&(p->endTime)), "%T") << " " << p->command
         << endl;
    }
    return os;
  }

  // find node according to the given pid, and remove it from linked list, then
  // return
  Node *findNodeByPid(int pid) {
    for (Node *pre{&(this->root)}; pre->next != nullptr; pre = pre->next)
      if (pre->next->pid == pid) {
        Node *temp = pre->next;
        pre->next = pre->next->next;
        this->size--;
        return temp;
      }
    return nullptr;
  }

  void insert(Node *node) {
    this->size++;
    node->next = this->root.next;
    node->endTime =
        chrono::system_clock::to_time_t(chrono::system_clock::now());
    this->root.next = node;
  }
};

class DoubleLinkedList {
private:
  int size{0};
  Node root{};

public:
  ~DoubleLinkedList() {
    Node *p{this->root.next}, *temp{nullptr};
    while (p != nullptr) {
      temp = p->next;
      delete p;
      p = temp;
    }
  }

  // show all active processes
  friend ostream &operator<<(ostream &os, const DoubleLinkedList &list) {
    os << "----- Active Processes -----" << endl;
    os << left << setw(5) << "PID"
       << " " << setw(10) << "USER"
       << " " << setw(5) << "CPU"
       << " "
       << "MEM"
       << " " << setw(4) << "STAT"
       << " " << setw(7) << "ETIMES"
       << " "
       << "COMMAND" << endl;
    for (Node *p{list.root.next}; p != nullptr; p = p->next) {
      os << left << setw(5) << p->pid << " " << setw(10) << p->user << " "
         << setiosflags(ios::fixed) << setprecision(1) << setw(5) << p->cpu
         << " " << p->mem << " " << setw(4) << p->stat << " " << setw(7)
         << p->elapsedTime << " " << p->command << endl;
    }
    return os;
  }

  Node *findNodeByPid(int pid) {
    for (Node *p{this->root.next}; p != nullptr; p = p->next)
      if (p->pid == pid) return p;
    return nullptr;
  }

  void insert(string user, int pid, double cpu, double mem, string stat,
              int elapsedTime, string command) {
    Node *node = new Node(user, pid, cpu, mem, stat, elapsedTime, command);
    Node *temp{this->root.next};
    this->root.next = node;
    node->pre = &(this->root);
    node->next = temp;
    if (temp != nullptr) temp->pre = node;
    this->size++;
  };

  // sort list by memory usage, using bubble sort
  void sort() {
    Node *pre{&(this->root)}, *temp{nullptr};
    for (size_t i = 1; i < this->size; i++) {
      for (size_t j = 0; j < this->size - i; j++) {
        if (pre->next->mem < pre->next->next->mem) {
          temp = pre->next;
          pre->next = temp->next;
          temp->next = temp->next->next;
          pre->next->next = temp;
          temp->pre = pre->next;
          pre->next->pre = pre;
          if (temp->next) temp->next->pre = temp;
        }
        pre = pre->next;
      }
      pre = &(this->root);
    }
  }

  // update list every second
  void update(string processes, LinkedList &l2) {
    int pid, elapsedTime;
    double cpu, mem;
    string user, command, stat;
    istringstream is(processes);
    // store all active processes' pid
    map<int, bool> pids;
    Node *node{nullptr};
    // process data using sstream
    while (!is.eof()) {
      is >> user >> pid >> cpu >> mem >> stat >> elapsedTime >> ws;
      getline(is, command);
      is >> ws;
      pids.emplace(pid, true);
      if (node = findNodeByPid(pid), node != nullptr) {
        // process already in the list
        node->cpu = cpu;
        node->mem = mem;
        node->stat = stat;
        node->elapsedTime = elapsedTime;
      } else if (node = l2.findNodeByPid(pid), node != nullptr) {
        // process in the finished list
        node->next = this->root.next;
        node->pre = &(this->root);
        this->root.next->pre = node;
        this->root.next = node;
        node->cpu = cpu;
        node->mem = mem;
        node->stat = stat;
        node->elapsedTime = elapsedTime;
        node->endTime = 0;
      } else {
        // add new process to list
        insert(user, pid, cpu, mem, stat, elapsedTime, command);
      }
    }
    Node *p{this->root.next}, *temp{nullptr};
    // move finished processes to the finished list
    while (p != nullptr) {
      auto search = pids.find(p->pid);
      temp = p->next;
      if (search == pids.end()) {
        p->pre->next = p->next;
        if (p->next) p->next->pre = p->pre;
        this->size--;
        l2.insert(p);
      }
      p = temp;
    }
    pids.clear();
    sort();
  }
};
