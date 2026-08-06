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

    int bestd = -1;

    // Binary search in each direction
    for (const auto &[diry, dirx] : directions) {
      // if (!(diry == 1 && dirx == 1)) continue; // FIXME only for debugging

      int maxdy = diry == 1 ? n - y : y - 1;
      int maxdx = dirx == 1 ? m - x : x - 1;
      int maxd = min(maxdy, maxdx);

      // if (maxd == 0) continue;

      // cerr << y << " " << x << " " << maxd << " " << diry << " " << dirx << "\n";
      cerr << "\n";
      cerr << "(" << y << ", " << x << ")" << "\n";

      int a = 0;
      int b = maxd;
      int d = -1;

      // Extend diagonally in one direction
      while (a <= b) {
        int mid = (a + b) / 2;
        int y2 = y + mid * diry;
        int x2 = x + mid * dirx;
        ll rocks = fw.query2(y, x, y2, x2);
        // cerr << mid << " " << rocks << "\n";
        if (rocks > 0) {
          // cerr << "rock\n";
          b = mid - 1;
        } else {
          // cerr << "not rock\n";
          d = mid;
          a = mid + 1;
        }
      }

      if (d == -1) continue;
      bestd = max(bestd, d);

      int d_result = d;

      // Try extending this in other directions
      cerr << "diry=" << diry << ", dirx=" << dirx << "\n";
      for (const auto &[diry2, dirx2] : directions) {
        // cerr << "diry2?=" << diry2 << ", dirx2?=" << dirx2 << "\n";
        if (diry2 == diry && dirx2 == dirx) continue;
        // Locked points
        int y2 = diry2 == diry ? y : y + d * diry;
        int x2 = dirx2 == dirx ? x : x + d * dirx;
        int maxdy2 = diry2 == 1 ? n - y2 : y2 - 1;
        int maxdx2 = dirx2 == 1 ? m - x2 : x2 - 1;
        int maxd2 = min(maxdy2, maxdx2);

        cerr << "(" << y2 << ", " << x2 << "), maxd2=" << maxd2 << ", diry2=" << diry2 << ", dirx2=" << dirx2 << "\n";

        int a = 0;
        int b = maxd2;
        int d2 = d;

        while (a <= b) {
          int mid = (a + b) / 2;
          int y3 = y2 + mid * diry2;
          int x3 = x2 + mid * dirx2;
          ll rocks = fw.query2(y2, x2, y3, x3);
          // cerr << mid << " " << rocks << "\n";
          if (rocks > 0) {
            // cerr << "rock\n";
            b = mid - 1;
          } else {
            // cerr << "not rock\n";
            d2 = mid;
            a = mid + 1;
            // cerr << "not rock at " << y2 << " " << x2 << " " << y3 << " " << x3 << "\n";
          }
        }

        // cerr << "d2: " << d2 << "\n";

        d_result = max(d_result, d2);
      }

      bestd = max(bestd, d_result);
    }

    ll result = (bestd+1)*(bestd+1);

    cout << result << "\n";
    // break; // FIXME only for debugging
  }
}
