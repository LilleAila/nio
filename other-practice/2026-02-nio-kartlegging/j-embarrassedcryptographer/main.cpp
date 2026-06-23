#include <iostream>
using namespace std;
using ll = long long;

const int TESTCASES = 50;

int mod(string x, int y, int i = 0, ll rem = 0) {
  if ((size_t)i == x.size()) return rem;
  int d = x[i] - '0';
  ll new_rem = (rem * 10 + d) % y;
  return mod(x, y, i+1, new_rem);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (true) {
    string k;
    int l;
    cin >> k >> l;

    if (k == "0") break;

    bool good = true;
    for (int i = 2; i < l; ++i) {
      if (mod(k, i) == 0) {
        cout << "BAD " << i << "\n";
        good = false;
        break;
      }
    }
    if (good) {
      cout << "GOOD" << "\n";
    }
  }
}
