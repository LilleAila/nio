#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
using namespace std;
using ll = long long;

array<pair<ll, ll>, 4> directions {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

struct DSU {
  vector<ll> parent, size;

  DSU(ll n) {
    size.assign(n, 1);
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
  }

  ll find(ll u) {
    // if (u == parent[u]) return u;
    // return parent[u] = find(parent[u]);
    // Iterative implementation:
    ll root = u;
    while (root != parent[root]) root = parent[root];
    while (u != root) {
      ll next = parent[u];
      parent[u] = root;
      u = next;
    }
    return root;
  }

  void join(ll u, ll v) {
    ll ru = find(u);
    ll rv = find(v);
    if (ru == rv) return;
    if (size[rv] > size[ru]) swap(ru, rv);
    parent[rv] = ru;
    size[ru] += size[rv];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  int t;
  cin >> n >> m >> t;

  vector<bool> bridge(n * m, false);
  DSU dsu(n * m);

  if (n <= 2) {
    cout << "0" << "\n";
    return 0;
  }

  for (ll i = 0; i < m; ++i) {
    bridge[i] = true;
    dsu.join(0, i);
    bridge[m*(n-1) + i] = true;
    dsu.join(m*(n-1), m*(n-1) + i);
  }

  for (int i = 0; i < t; ++i) {
    ll r, c;
    cin >> r >> c;
    ll u = r * m + c;
    bridge[u] = true;

    // cerr << r << " " << c << " " << u << "\n";

    for (const auto &[dy, dx] : directions) {
      ll r2 = r + dy;
      ll c2 = c + dx;
      if (r2 < 0 || c2 < 0 || r2 >= n || c2 >= m) continue;
      ll v = r2 * m + c2;
      if (bridge[v]) dsu.join(u, v);
    }

    if (dsu.find(0) == dsu.find(m * (n-1))) {
      cout << i+1 << "\n";
      return 0;
    }
  }

  cout << "nej" << "\n";
}
