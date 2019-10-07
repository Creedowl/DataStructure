/*
 * @Date: 2019-10-07 14:22:38
 * @Author: creedowl
 * @Description: e2p4 (csp)
 */
#include <iostream>
using namespace std;

int t1[1000001];
int n, ai, bi, ci, di;
int total = 0;

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ai >> bi;
    for (int j = ai; j < bi; j++) t1[j] = 1;
  }
  for (int i = 0; i < n; i++) {
    cin >> ci >> di;
    for (int j = ci; j < di; j++)
      if (t1[j]) total++;
  }
  cout << total << endl;
}
