#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <algorithm>
#include <array>
using namespace std;
using ll = long long;

const array<pair<int, int>, 4> directions {{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};

template <typename T> struct FenwickTree {
  int n;
  int m;
  vector<vector<T>> bit;

  FenwickTree(int n, int m) : n(n), m(m), bit(n + 1, vector<T>(m + 1, 0)) {};

  void update(int y, int x, T d) {
    for (int i = y; i <= n; i += i & -i) {
      for (int j = x; j <= m; j += j & -j) {
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

  T query2(int y1, int x1, int y2, int x2) {
    int min_y = min(y1, y2);
    int max_y = max(y1, y2);
    int min_x = min(x1, x2);
    int max_x = max(x1, x2);
    return query(min_y, min_x, max_y, max_x);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  FenwickTree<ll> fw(n, m);
  vector<vector<bool>> rock(n+1, vector<bool>(m+1, false));
  for (int y = 1; y <= n; ++y) {
    for (int x = 1; x <= m; ++x) {
      char c;
      cin >> c;
      if (c == '#') {
        fw.update(y, x, 1);
        rock[y][x] = true;
      }
    }
  }

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    int y, x;
    cin >> y >> x;

    if (rock[y][x]) {
      cout << "0" << "\n";
      continue;
    }

    int bestd = 0;
    int cy = y;
    int cx = x;

    // Binary search in each direction
    int diry_prev = 0;
    int dirx_prev = 0;
    int d = 0;
    for (int i = 0; i < 4; ++i) {
      int next_d = d;
      int next_diry = diry_prev;
      int next_dirx = dirx_prev;
      int next_y = cy;
      int next_x = cx;
      for (const auto &[diry, dirx] : directions) {
        if (i > 0 && diry == diry_prev && dirx == dirx_prev) continue;
        int y = (i == 0 || diry == diry_prev) ? cy : cy + d * diry_prev;
        int x = (i == 0 || dirx == dirx_prev) ? cx : cx + d * dirx_prev;
        int maxdy = diry == 1 ? n - y : y - 1;
        int maxdx = dirx == 1 ? m - x : x - 1;
        int maxd = min(maxdy, maxdx);

        int a = 0;
        int b = maxd;
        int d2 = -1;

        while (a <= b) {
          int mid = (a + b) / 2;
          int y2 = y + mid * diry;
          int x2 = x + mid * dirx;
          ll rocks = fw.query2(y, x, y2, x2);
          if (rocks > 0) {
            b = mid - 1;
          } else {
            d2 = mid;
            a = mid + 1;
          }
        }

        if (d2 != -1 && d2 > next_d) {
          next_d = d2;
          next_diry = diry;
          next_dirx = dirx;
          next_y = y;
          next_x = x;
        }
      }

      if (next_d == d && i > 0) break;
      d = next_d;
      diry_prev = next_diry;
      dirx_prev = next_dirx;
      cy = next_y;
      cx = next_x;
      bestd = max(bestd, d);
    }

    ll result = (bestd+1)*(bestd+1);

    cout << result << "\n";
    // break; // FIXME only for debugging
  }
}
