/*
 * @Date: 2020-01-07 14:06:30
 * @Author: creedowl
 * @Description: queue
 */
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
  int cur_people, end_time;
} Windows;

typedef struct {
  int peo, pri, begin, total, leave;
} Client;

vector<Client> c;

Windows w[3];

int main() {
  auto fp = freopen("data.in", "r", stdin);
  vector<Client> q;
  int peo, pri, begin, total, leave;
  while (!cin.eof()) {
    cin >> peo >> pri >> begin >> total >> leave >> ws;
    Client cc;
    cc.peo = peo;
    cc.pri = pri;
    cc.begin = begin;
    cc.total = total;
    cc.leave = leave;
    c.push_back(cc);
  }
  int t{0};
  while (!c.empty() or !q.empty()) {
    for (auto i = c.begin(); i != c.end();) {
      if (i->begin == t) {
        if (q.empty()) {
          q.push_back(*i);
          c.erase(i);
        } else {
          bool flag{false};
          for (auto it = q.rbegin(); it != q.rend(); it++) {
            if (it->pri >= i->pri) {
              q.insert(it.base(), *i);
              c.erase(i);
              flag = true;
              break;
            }
          }
          if (!flag) {
            q.insert(q.begin(), *i);
            c.erase(i);
          }
        }
      } else {
        i++;
      }
    }
    for (size_t i = 0; i < 3; i++) {
      if (q.empty()) break;
      if (w[i].end_time <= t) {
        w[i].cur_people = q.front().peo;
        w[i].end_time = t + q.front().total;
        cout << q.front().peo << "等待了" << t - q.front().begin << "分钟"
             << endl;
        q.erase(q.begin());
      }
    }

    t++;
  }

  fclose(fp);
}
