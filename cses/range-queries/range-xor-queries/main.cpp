#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
  int n;
  vector<int> tree;

  FenwickTree(int n) : n(n), tree(n + 1, 0) {};

  void update(int i, int d) {
    for (; i <= n; i += (i & -i)) {
      tree[i] ^= d;
    }
  }

  int query(int i) const {
    int result = 0;
    for (; i > 0; i -= (i & -i)) {
      result ^= tree[i];
    }
    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  FenwickTree fw(n);
  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;
    fw.update(i, x);
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    int result = fw.query(b) ^ fw.query(a - 1);
    cout << result << endl;
  }
}
