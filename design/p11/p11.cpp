/*
 * @Date: 2020-01-03 20:37:30
 * @Author: creedowl
 * @Description: csp (201803-3)
 */
#include <iostream>
#include <vector>

using namespace std;

class Pattern {
public:
  string name, ori;
  // second is parameter type, 0: url string, 1: int, 2: string, 3: path
  vector<pair<string, int>> parameters;

  bool isNum(char ch) {
    if (ch >= '0' and ch <= '9') return true;
    return false;
  }

  void create(string urlPattern, string name) {
    this->ori = urlPattern;
    this->name = name;
    if (urlPattern.back() != '/') urlPattern.push_back('/');
    int begin{1};
    int pos = urlPattern.find("/", 1);
    string str;
    while (pos != string::npos) {
      int type{0};
      str = urlPattern.substr(begin, pos - begin);
      if (str == "<int>")
        type = 1;
      else if (str == "<str>")
        type = 2;
      else if (str == "<path>")
        type = 3;
      parameters.push_back({str, type});
      begin = pos + 1;
      pos = urlPattern.find("/", begin);
    }
  }

  bool resolve(string url) {
    if (this->ori.back() == '/' and url.back() != '/') return false;
    if (this->ori.back() != '/' and url.back() == '/') return false;

    bool tail{false};
    if (url.back() != '/') {
      url.push_back('/');
      tail = true;
    }
    int begin{1}, cur{0}, pos = url.find("/", 1);
    vector<string> result;
    string str;
    while (pos != string::npos) {
      if (cur > this->parameters.size() - 1) return false;
      int type = this->parameters[cur].second;
      str = url.substr(begin, pos - begin);
      if (type == 0) {
        if (!(this->parameters[cur].first == str)) {
          return false;
        } else {
          // result.push_back(str);
        }
      } else if (type == 1) {
        string num;
        for (size_t i = 0; i < str.size(); i++) {
          if (!isNum(str[i])) {
            return false;
          } else {
            if (i == 0 and str[0] == '0' and str.size() != 1) continue;
            num.push_back(str[i]);
          }
        }
        result.push_back(num);
      } else if (type == 2) {
        result.push_back(str);
      } else if (type == 3) {
        int end = tail ? url.size() - begin - 1 : url.size() - begin;
        result.push_back(url.substr(begin, end));
        break;
      }
      cur++;
      begin = pos + 1;
      pos = url.find("/", begin);
    }
    if (cur < this->parameters.size() - 1) return false;
    cout << this->name << " ";
    for (auto &i : result) cout << i << " ";
    cout << endl;
    return true;
  }
};

vector<Pattern> patterns(101);

int main() {
  int n, m;
  string urlPattern, name, url;
  cin >> n >> m;
  for (size_t i = 0; i < n; i++) {
    cin >> urlPattern >> name;
    patterns[i].create(urlPattern, name);
  }
  bool flag{false};
  for (size_t i = 0; i < m; i++) {
    flag = false;
    cin >> url;
    for (auto &ch : url)
      if (!(ch >= '0' and ch <= '9') and !(ch >= 'a' and ch <= 'z') and
          !(ch >= 'A' and ch <= 'Z') and !(ch == '/') and !(ch == '-') and
          !(ch == '_') and !(ch == '.')) {
        break;
      }
    for (size_t j = 0; j < n; j++) {
      if (patterns[j].resolve(url)) {
        flag = true;
        break;
      }
    }
    if (!flag) cout << 404 << endl;
  }
}
