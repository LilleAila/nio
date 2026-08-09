#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
#include <unordered_map>
#include <unordered_set>
using namespace std;
using ll = long long;

array<pair<ll, ll>, 4> directions {{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

struct DSU {
  unordered_map<ll, ll> parent, size;

  DSU() {}

  ll find(ll u) {
    auto par = parent.find(u);
    if (par == parent.end()) {
      parent[u] = u;
      return u;
    }
    ll p = (*par).second;
    if (p == u) return u;
    return parent[u] = find(p);
  }

  void join(ll u, ll v) {
    ll ru = find(u);
    ll rv = find(v);
    if (ru == rv) return;
    auto su_it = size.find(ru);
    ll su = su_it == size.end() ? 1 : (*su_it).second;
    auto sv_it = size.find(rv);
    ll sv = sv_it == size.end() ? 1 : (*sv_it).second;
    if (sv > su) swap(ru, rv);
    parent[rv] = ru;
    size[ru] = su + sv;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  int t;
  cin >> n >> m >> t;

  unordered_set<ll> bridge;
  DSU dsu;

  if (n <= 2) {
    cout << "0" << "\n";
    return 0;
  }

  // for (ll i = 0; i < m; ++i) {
  //   bridge.insert(i);
  //   dsu.join(0, i);
  //   bridge.insert(m*(n-1) + i);
  //   dsu.join(m*(n-1), m*(n-1) + i);
  // }

  for (int i = 0; i < t; ++i) {
    ll r, c;
    cin >> r >> c;
    ll u = r * m + c;
    bridge.insert(u);

    // cerr << r << " " << c << " " << u << "\n";

    for (const auto &[dy, dx] : directions) {
      ll r2 = r + dy;
      ll c2 = c + dx;
      if (r2 < 0 || c2 < 0 || r2 >= n || c2 >= m) continue;
      if (r2 == 0) dsu.join(u, 0);
      else if (r2 == n-1) dsu.join(u, m * (n-1));
      else {
        ll v = r2 * m + c2;
        if (bridge.find(v) != bridge.end()) dsu.join(u, v);
      }
    }

    if (dsu.find(0) == dsu.find(m * (n-1))) {
      cout << i+1 << "\n";
      return 0;
    }
  }

  cout << "nej" << "\n";
}
