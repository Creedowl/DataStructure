/*
 * @Date: 2019-12-24 13:55:12
 * @Author: creedowl
 * @Description: Evaluate expression
 */
#include <iostream>
#include <vector>

using namespace std;

class Expression {
private:
  string expression;
  int pos{0};
  vector<char> optr;
  vector<double> opnd;

  void showError(string error, int p = -1) {
    cout << "Error: " << error << endl << this->expression << endl;
    if (p == -1) p = this->pos - 1;
    for (size_t i = 0; i < p; i++) cout << "-";
    cout << "^" << endl;
    exit(1);
  }

  // show stack
  void show() {
    cout << "optr stack: ";
    for (auto &i : this->optr) cout << i << " ";
    cout << endl << "opnd stack: ";
    for (auto &i : this->opnd) cout << i << " ";
    cout << endl;
  }

  int isLegal(char ch) {
    // operator
    if (ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '(' or
        ch == ')' or ch == '#')
      return 1;
    // number
    if (ch >= '0' and ch <= '9') return 2;
    // dot
    if (ch == '.') return 3;
    // illegal
    return 0;
  }

  // compare the precedence of two operators, true means high priority
  bool compare(char top, char ch) {
    if (top == '#' or top == '(') return false;
    if (top == ')') return true;
    if (top == '+' or top == '-') {
      if (ch == '*' or ch == '/' or ch == '(') return false;
      return true;
    }
    if (top == '*' or top == '/') {
      if (ch == '(') return false;
      return true;
    }
    return false;
  }

  double calculate(double a, double b, char opr) {
    if (opr == '+') return a + b;
    if (opr == '-') return a - b;
    if (opr == '*') return a * b;
    if (opr == '/') {
      if (b == 0) showError("division by zero is undefined", this->pos - 1);
      return a / b;
    }
    return 0;
  }

  // skip all blank
  char getCh() {
    char ch;
    do {
      if (this->pos >= this->expression.size()) return '#';
      ch = this->expression[this->pos++];
    } while (ch == ' ');
    return ch;
  }

public:
  void evaluate() {
    char ch;
    int legal{0};
    getline(cin, this->expression);
    ch = getCh();

    // check expression's begin and end
    if (ch != '#') return showError("expression must begin with '#'");
    if (expression[expression.size() - 1] != '#')
      return showError("expression must end with '#'", this->expression.size());

    // check brackets
    vector<int> brackets;
    for (size_t i = 0; i < this->expression.size(); i++) {
      if (this->expression[i] == '(') brackets.push_back(i);
      if (this->expression[i] == ')') brackets.pop_back();
    }
    if (brackets.size() != 0)
      return showError("invalid syntax", brackets.front());

    // operator stack starts with '#'
    optr.push_back(ch);
    while (this->pos < this->expression.size()) {
      // show stack
      show();
      ch = getCh();
      legal = isLegal(ch);
      if (legal == 0) return showError("the char is not legal");
      if (legal == 1) {
        // operator
        // calculate and add to opnd
        while (compare(optr.back(), ch)) {
          double a{0}, b{0};
          b = opnd.back();
          opnd.pop_back();
          a = opnd.back();
          opnd.pop_back();
          opnd.push_back(calculate(a, b, optr.back()));
          optr.pop_back();
        }
        // expression ended, the last number in opnd is answer
        if (ch == optr.back() and ch == '#') {
          cout << opnd.back() << endl;
          return;
        }
        // remove brackets when ch == top
        if (ch == ')' and optr.back() == '(')
          optr.pop_back();
        else
          optr.push_back(ch);
      } else if (legal == 2) {
        // number
        double num{0};
        // integral part
        do {
          num = num * 10 + int(ch - '0');
          ch = getCh();
        } while (isLegal(ch) == 2);
        // fractional part
        if (isLegal(ch) == 3) {
          int level{10};
          ch = getCh();
          do {
            // multi dots error
            if (isLegal(ch) == 3) return showError("multi dots in number");
            num += double(ch - '0') / level;
            level *= 10;
            ch = getCh();
          } while (isLegal(ch) == 2);
          // multi dots error
          if (isLegal(ch) == 3) return showError("multi dots in number");
        }
        opnd.push_back(num);
        this->pos--;
      }
    }
  }
};

int main() {
  Expression e;
  e.evaluate();
}
