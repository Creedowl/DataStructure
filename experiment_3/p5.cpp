/*
 * @Date: 2019-10-21 15:28:07
 * @Author: creedowl
 * @Description: e3p5 (csp)
 */
#include <iostream>
#include <vector>
using namespace std;

int m, n;

struct pos {
  int x, y;
};

class windows {
private:
  pos p1, p2;
  int layout;

public:
  windows() = default;
  windows(int x1, int y1, int x2, int y2, int layout) {
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    windows::layout = layout;
  }

  bool inside(pos p) {
    return p.x >= p1.x and p.x <= p2.x and p.y >= p1.y and p.y <= p2.y;
  }

  int getLayout() { return layout; }
};

vector<windows> list;

int main() {
  cin >> n >> m;
  int x1, y1, x2, y2;
  int layout = 1;

  for (size_t i = 0; i < n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    list.push_back(windows(x1, y1, x2, y2, layout++));
  }

  pos ope;
  bool flag = false;
  windows temp;

  for (size_t i = 0; i < m; i++) {
    cin >> ope.x >> ope.y;
    for (auto r_iter = list.rbegin(); r_iter != list.rend(); r_iter++) {
      if (r_iter->inside(ope)) {
        cout << r_iter->getLayout() << endl;
        temp = *r_iter;
        list.erase((++r_iter).base());
        list.push_back(temp);
        flag = true;
        break;
      }
    }
    if (!flag) cout << "IGNORED" << endl;
    flag = false;
  }
}
