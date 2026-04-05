#include <iostream>
#include <vector>
using namespace std;

template <typename T> struct FenwickTree {
  int n;
  vector<vector<T>> bit;

  FenwickTree(int n) : n(n), bit(n + 1, vector<T>(n + 1, 0)) {};

  void update(int y, int x, T d) {
    for (int i = y; i <= n; i += i & -i) {
      for (int j = x; j <= n; j += j & -j) {
        bit[i][j] += d;
      }
    }
  }

  T query(int y, int x) const {
    T result = 0;
    for (int i = y; i > 0; i -= i & -i) {
      for (int j = x; j > 0; j -= j & -j) {
        result += bit[i][j];
      }
    }
    return result;
  }

  T query(int y1, int x1, int y2, int x2) {
    return query(y2, x2) - query(y2, x1 - 1) - query(y1 - 1, x2) +
           query(y1 - 1, x1 - 1);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  FenwickTree<long long> ft(n);

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;

    for (int j = 0; j < n; ++j) {
      bool tree = s[j] == '*';
      if (tree) {
        ft.update(i + 1, j + 1, 1);
      }
    }
  }

  while (q--) {
    int y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    cout << ft.query(y1, x1, y2, x2) << endl;
  }
}
