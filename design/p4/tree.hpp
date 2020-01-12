/*
 * @Date: 2020-01-04 16:59:52
 * @Author: creedowl
 * @Description: tree data structrue
 */
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

class Member {
public:
  int id, generation;
  bool married{false};
  string name, address;
  int birth_y, birth_m, birth_d, death_y{-1}, death_m{-1}, death_d{-1};
  Member *firstChild{nullptr}, *nextSibling{nullptr}, *parent{nullptr};

  Member() = default;

  Member(int id, int generation, int parentId, bool married, string name,
         string address, int birth_y, int birth_m, int birth_d, int death_y,
         int death_m, int death_d)
      : id(id),
        generation(generation),
        married(married),
        name(name),
        address(address),
        birth_y(birth_y),
        birth_m(birth_m),
        birth_d(birth_d),
        death_y(death_y),
        death_m(death_m),
        death_d(death_d) {}

  string getBirthDay() {
    ostringstream os;
    os << this->birth_y << "-" << this->birth_m << "-" << this->birth_d;
    return os.str();
  }

  string getDeathDate() {
    ostringstream os;
    os << this->death_y << "-" << this->death_m << "-" << this->death_d;
    return os.str();
  }

  bool alive() {
    return this->death_y == -1 and this->death_m == -1 and this->death_d == -1;
  }

  string toString() {
    ostringstream os;
    int parentId = this->parent != nullptr ? this->parent->id : -1;
    os << this->id << " " << this->generation << " " << parentId << " "
       << this->married << " " << this->name << " " << this->address << " "
       << this->birth_y << " " << this->birth_m << " " << this->birth_d << " "
       << this->death_y << " " << this->death_m << " " << this->death_d;
    return os.str();
  }
};

class FamilyTree {
private:
  int total{0}, generation{0};

  bool extractDate(const string &s, int &y, int &m, int &d) {
    if (s != "") {
      istringstream is(s);
      char delimiter;
      if (!(is >> y >> delimiter >> m >> delimiter >> d)) return false;
    }
    struct tm t = {0};
    t.tm_year = y - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = d;
    t.tm_isdst = -1;
    time_t when = mktime(&t);
    const struct tm *norm = localtime(&when);
    return (norm->tm_year == y - 1900 && norm->tm_mon == m - 1 &&
            norm->tm_mday == d);
  }

public:
  Member ancestor{};

  FamilyTree() {}

  ~FamilyTree() {
    queue<Member *> q{{this->ancestor.firstChild}}, rm;
    Member *cur{nullptr};
    while (!q.empty()) {
      cur = q.front();
      rm.push(cur);
      q.pop();
      if (cur->firstChild != nullptr) q.push(cur->firstChild);
      while (cur->nextSibling != nullptr) {
        cur = cur->nextSibling;
        rm.push(cur);
        if (cur->firstChild != nullptr) q.push(cur->firstChild);
      }
    }
    while (!rm.empty()) {
      delete rm.front();
      rm.pop();
    }
  }

  Member *findMember(int id = -1, string name = "") {
    queue<Member *> q{{this->ancestor.firstChild}};
    Member *cur{nullptr};
    while (!q.empty()) {
      cur = q.front();
      if (id != -1 and cur->id == id) return cur;
      if (id == -1 and cur->name == name) return cur;
      q.pop();
      if (cur->firstChild != nullptr) q.push(cur->firstChild);
      while (cur->nextSibling != nullptr) {
        cur = cur->nextSibling;
        if (id != -1 and cur->id == id) return cur;
        if (id == -1 and cur->name == name) return cur;
        if (cur->firstChild != nullptr) q.push(cur->firstChild);
      }
    }
    return nullptr;
  }

  bool removeMemberAndChildren(int id = -1, string name = "") {
    Member *member;
    if (id == -1)
      member = findMember(-1, name);
    else
      member = findMember(id);

    bool flag{false};
    queue<Member *> q{{this->ancestor.firstChild}}, rm;
    Member *cur{nullptr};
    while (!q.empty()) {
      cur = q.front();
      if (cur == member) {
        flag = true;
        // rm.push(cur);
      }
      if (flag) rm.push(cur);
      q.pop();
      if (cur->firstChild != nullptr) q.push(cur->firstChild);
      while (cur->nextSibling != nullptr) {
        cur = cur->nextSibling;
        if (cur == member) {
          flag = true;
          while (!q.empty()) q.pop();
          q.push(cur);

          if (cur->parent == nullptr) {
            this->ancestor.firstChild = nullptr;
            this->total = 0;
          } else {
            Member *preSibling{cur->parent->firstChild};
            if (preSibling == cur) {
              cur->parent->firstChild = nullptr;
            } else {
              while (!(preSibling->nextSibling == cur))
                preSibling = preSibling->nextSibling;
              preSibling->nextSibling = cur->nextSibling;
            }
          }

          break;
        }
        if (flag) rm.push(cur);
        if (cur->firstChild != nullptr) q.push(cur->firstChild);
      }
    }
    while (!rm.empty()) {
      delete rm.front();
      this->total--;
      rm.pop();
    }
    return true;
  }

  void showMemberInfo(int id = -1, string name = "") {
    Member *member;
    if (id == -1)
      member = findMember(-1, name);
    else
      member = findMember(id);
    if (member == nullptr) {
      cout << "找不到该成员，请检查输入的姓名" << endl;
      return;
    }
    cout << "姓名: " << member->name << " ID: " << member->id
         << " 生日: " << member->getBirthDay() << " 地址: " << member->address
         << " 辈分: " << member->generation << " 婚姻状态: ";
    if (member->married)
      cout << "已婚 ";
    else
      cout << "未婚 ";
    if (!member->alive()) cout << " 死亡日期: " << member->getDeathDate();
    cout << endl;
    if (member->parent != nullptr) {
      cout << "父亲: " << member->parent->name;
    }
    if (member->firstChild != nullptr) {
      Member *child = member->firstChild;
      cout << " 儿子: ";
      while (child != nullptr) {
        cout << child->name << " ";
        child = child->nextSibling;
      }
    }
    cout << endl;
  }

  void showAll() {
    cout << "总人数: " << this->total << endl;
    int level{1};
    Member *member{nullptr};
    for (size_t i = 0; i < this->total; i++) {
      member = this->findMember(i);
      if (!member) break;
      if (member->generation > level) {
        cout << endl;
        level = member->generation;
      }
      cout << member->name << " ";
    }
    cout << endl;
  }

  void showGeneration(int g) {
    cout << "第" << g << "代人有: ";
    Member *member{nullptr};
    for (size_t i = 0; i < this->total; i++) {
      member = findMember(i);
      if (!member) break;
      if (member->generation != g) {
        continue;
      }
      cout << member->name << " ";
    }
    cout << endl;
  }

  bool relation(string a, string b) {
    Member *p1{nullptr}, *p2{nullptr};
    p1 = findMember(-1, a);
    if (p1 == nullptr) {
      cout << "找不到" << a << endl;
      return false;
    }
    p2 = findMember(-1, b);
    if (p2 == nullptr) {
      cout << "找不到" << b << endl;
      return false;
    }
    if (p1->parent == p2) {
      cout << b << "是" << a << "的父亲" << endl;
    } else if (p2->parent == p1) {
      cout << a << "是" << b << "的父亲" << endl;
    }
    return true;
  }

  bool queryByBirthday(string birthday) {
    int y, m, d;
    if (!extractDate(birthday, y, m, d)) {
      cout << "生日信息错误" << endl;
      return false;
    }
    cout << "生日为" << birthday << "的成员有: " << endl;
    Member *member{nullptr};
    for (size_t i = 0; i < this->total; i++) {
      member = findMember(i);
      if (member == nullptr) return false;
      if (member->birth_y == y and member->birth_m == m and
          member->birth_d == d) {
        showMemberInfo(i);
      }
    }
    return true;
  }

  bool updateMemberInfo(string name) {
    Member *member = findMember(-1, name);
    if (member == nullptr) {
      cout << "找不到该成员，请检查姓名" << endl;
      return false;
    }
    string address, birthday, deathdate;
    int married;
    cout << "请输入新的成员信息: 姓名 婚否 地址 生日 死亡日期" << endl;
    cin >> name >> married >> address >> birthday >> deathdate;
    int birth_y, birth_m, birth_d, death_y, death_m, death_d;
    if (!extractDate(birthday, birth_y, birth_m, birth_d)) {
      cout << "生日信息错误" << endl;
      return false;
    }
    if (!extractDate(deathdate, death_y, death_m, death_d)) {
      cout << "死亡日期错误" << endl;
      return false;
    }
    member->name = name;
    member->married = married;
    member->address = address;
    member->birth_y = birth_y;
    member->birth_m = birth_m;
    member->birth_d = birth_d;
    member->death_y = death_y;
    member->death_m = death_m;
    member->death_d = death_d;
    return true;
  }

  bool addMember(string name, string parent, bool married, string address,
                 string birthday, string deathdate) {
    int birth_y, birth_m, birth_d, death_y, death_m, death_d;
    if (!extractDate(birthday, birth_y, birth_m, birth_d)) {
      cout << "生日信息错误" << endl;
      return false;
    }
    if (!extractDate(deathdate, death_y, death_m, death_d)) {
      cout << "死亡日期错误" << endl;
      return false;
    }
    Member *par = findMember(-1, parent);
    if (par == nullptr) {
      cout << "找不到父亲" << endl;
      return false;
    }
    addMember(par->id, married, name, address, birth_y, birth_m, birth_d,
              death_y, death_m, death_d);
    return true;
  }

  bool addMember(int parentId, bool married, string name, string address,
                 int birth_y, int birth_m, int birth_d, int death_y,
                 int death_m, int death_d) {
    // check birthday
    if (!extractDate("", birth_y, birth_m, birth_d)) {
      cout << "生日信息错误" << endl;
      return false;
    }
    // check death date
    if (!extractDate("", death_y, death_m, death_d) and
        !(death_y == -1 and death_m == -1 and death_d == -1)) {
      cout << "死亡日期错误" << endl;
      return false;
    }
    // find parent
    if (parentId == -1 and this->ancestor.firstChild != nullptr) {
      cout << "已经有祖先" << endl;
      return false;
    }
    int id = this->total;
    Member *member =
        new Member(id, -1, parentId, married, name, address, birth_y, birth_m,
                   birth_d, death_y, death_m, death_d);
    if (parentId == -1) {
      this->ancestor.firstChild = member;
      member->generation = 1;
      this->generation = 1;
      // member->parent = &(this->ancestor);
    } else {
      member->parent = this->findMember(parentId);
      if (member->parent == nullptr) {
        cout << "找不到父亲" << endl;
        delete member;
        return false;
      }
      member->generation = member->parent->generation + 1;
    }
    // find siblings
    if (parentId != -1) {
      if (member->parent->firstChild == nullptr)
        member->parent->firstChild = member;
      else {
        Member *sibling = member->parent->firstChild;
        while (sibling->nextSibling != nullptr) sibling = sibling->nextSibling;
        sibling->nextSibling = member;
      }
    }
    this->total++;
    this->generation = max(this->generation, member->generation);
    return true;
  }

  bool loadData(string fileName) {
    fstream f(fileName);
    if (!f) {
      cout << "找不到文件 " << fileName << endl;
      return false;
    }
    int total{0};
    f >> total >> this->generation >> ws;
    string buffer;
    int id, birth_y, birth_m, birth_d, death_y, death_m, death_d, partner_id,
        married, generation;
    string name, address;
    int line{1};
    for (int i = 0; i < total; i++) {
      getline(f, buffer);
      line++;
      istringstream is(buffer);
      while (!is.eof()) {
        is >> id >> generation >> partner_id >> married >> name >> address >>
            birth_y >> birth_m >> birth_d >> death_y >> death_m >> death_d >>
            ws;
        if (!this->addMember(partner_id, married, name, address, birth_y,
                             birth_m, birth_d, death_y, death_m, death_d)) {
          cout << "文件数据损坏: line" << line << endl;
          return false;
        }
      }
      if (f.eof()) break;
    }
    f.close();
    cout << "加载成功" << endl;
    return true;
  }

  bool saveData(string fileName) {
    fstream f(fileName, ios::out);
    if (!f) {
      cout << "找不到文件 " << fileName << endl;
      return false;
    }
    f << this->total << " " << this->generation << endl;
    queue<Member *> q{{this->ancestor.firstChild}};
    Member *cur{nullptr};
    while (!q.empty()) {
      cur = q.front();
      // rm.push(cur);
      f << cur->toString() << endl;
      q.pop();
      if (cur->firstChild != nullptr) q.push(cur->firstChild);
      while (cur->nextSibling != nullptr) {
        cur = cur->nextSibling;
        // rm.push(cur);
        f << cur->toString() << endl;
        if (cur->firstChild != nullptr) q.push(cur->firstChild);
      }
    }
    f.close();
    cout << "保存成功" << endl;
    return true;
  }
};
