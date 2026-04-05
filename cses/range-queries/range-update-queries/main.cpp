#include <iostream>
#include <vector>
using namespace std;

template <typename T> struct FenwickTree {
  int n;
  vector<T> bit;

  FenwickTree(int n) : n(n), bit(n + 2, T(0)) {};

  void update(int i, T d) {
    for (; i <= n; i += i & -i) {
      bit[i] += d;
    }
  }

  void update(int i, int j, T d) {
    update(i, d);
    update(j + 1, -d);
  }

  T query(int i) const {
    T result = 0;
    for (; i > 0; i -= i & -i) {
      result += bit[i];
    }
    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  FenwickTree<long long> ft(n);
  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;
    ft.update(i, i, x);
  }

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int a, b, u;
      cin >> a >> b >> u;
      ft.update(a, b, u);
    } else {
      int k;
      cin >> k;
      cout << ft.query(k) << endl;
    }
  }
}
