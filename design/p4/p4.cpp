/*
 * @Date: 2020-01-04 16:29:56
 * @Author: creedowl
 * @Description: family tree
 */
#include <iostream>
#include "tree.hpp"

using namespace std;

void showHelp() {
  cout << "0: 展示帮助" << endl;
  cout << "1: 显示所有成员" << endl;
  cout << "2: 添加成员" << endl;
  cout << "3: 加载数据" << endl;
  cout << "4: 保存数据" << endl;
  cout << "5: 根据姓名查询成员信息" << endl;
  cout << "6: 显示第n代所有人的信息" << endl;
  cout << "7: 按照出生日期查询成员名单" << endl;
  cout << "8: 输入两人姓名，确定其关系" << endl;
  cout << "9: 删除某成员" << endl;
  cout << "10: 修改某成员信息" << endl;
  cout << "11: 退出" << endl;
}

int main() {
  FamilyTree tree{};
  // tree.loadData("data.txt");
  // tree.addMember(-1, true, "A", "Qwer", 2000, 1, 1, 2001, 1, 1);
  // tree.addMember(0, true, "B", "bbb", 2000, 2, 29, -1, -1, -1);
  // tree.addMember(0, true, "C", "ccc", 2000, 2, 1, -1, -1, -1);
  // tree.addMember(0, true, "D", "ddd", 2000, 2, 1, -1, -1, -1);
  // tree.addMember(1, false, "E", "eee", 2000, 2, 1, -1, -1, -1);
  // tree.addMember(1, false, "F", "fff", 2000, 2, 1, -1, -1, -1);
  // tree.addMember(3, false, "G", "ggg", 2000, 2, 1, -1, -1, -1);
  // tree.addMember(6, false, "H", "hhh", 2000, 2, 1, -1, -1, -1);
  // tree.addMember(6, false, "I", "iii", 2000, 2, 1, -1, -1, -1);
  // Member *member = tree.findMember(1);
  // cout << member->toString() << endl;
  // tree.showMemberInfo(-1, "C");
  // tree.showAll();
  // tree.showGeneration(4);
  // tree.relation("G", "H");
  // tree.queryByBirthday("2000-2-1");
  // tree.removeMemberAndChildren(1);
  // tree.saveData("data.txt");
  int opt{0};
  showHelp();
  while (true) {
    cout << "请输入操作符: " << endl;
    cin >> opt;
    if (opt == 0) {
      showHelp();
    } else if (opt == 1) {
      tree.showAll();
    } else if (opt == 2) {
      cout << "请依次输入成员信息: 姓名 父亲 婚否 地址 生日 死亡日期" << endl;
      string name, address, birthday, deathdate, parent;
      int married;
      cin >> name >> parent >> married >> address >> birthday >> deathdate;
      if (tree.addMember(name, parent, married, address, birthday, deathdate)) {
        cout << "添加成功" << endl;
      }
    } else if (opt == 3) {
      tree.loadData("data.txt");
    } else if (opt == 4) {
      tree.saveData("data.txt");
    } else if (opt == 5) {
      string name;
      cout << "请输入姓名" << endl;
      cin >> name;
      tree.showMemberInfo(-1, name);
    } else if (opt == 6) {
      int g;
      cout << "请输入第n代人" << endl;
      cin >> g;
      tree.showGeneration(g);
    } else if (opt == 7) {
      string birthday;
      cout << "请输入生日" << endl;
      cin >> birthday;
      tree.queryByBirthday(birthday);
    } else if (opt == 8) {
      string a, b;
      cout << "请输入两个人的姓名" << endl;
      cin >> a >> b;
      tree.relation(a, b);
    } else if (opt == 9) {
      string name;
      cout << "请输入成员姓名" << endl;
      cin >> name;
      tree.removeMemberAndChildren(-1, name);
    } else if (opt == 10) {
      string name;
      cout << "请输入成员姓名" << endl;
      cin >> name;
      tree.updateMemberInfo(name);
    } else if (opt == 11) {
      exit(0);
    }
  }
}
