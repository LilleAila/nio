#include <iostream>
#include <climits>
#include <functional>
#include <tuple>
#include <map>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>
using namespace std;
using ll = long long;

struct DSU {
  vector<int> parent;
  vector<int> size;

  DSU(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    size.assign(n, 1);
  }

  int find(int u) {
    int p = parent[u];
    if (p != u) {
      return parent[u] = find(p);
    }
    return p;
  }

  bool unite(int u, int v) {
    int p_u = find(u);
    int p_v = find(v);

    if (p_u == p_v) {
      return false;
    }

    if (size[p_v] > size[p_u]) {
      swap(p_u, p_v);
    }

    parent[p_v] = p_u;
    size[p_u] += size[p_v];
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<pair<ll, ll>> houses(n);
  map<ll, vector<int>> xs;
  for (int i = 0; i < n; ++i) {
    cin >> houses[i].first >> houses[i].second;
    xs[houses[i].first].push_back(i);
  }

  vector<tuple<ll, int, int>> edges;

  for (auto it = xs.begin(); it != xs.end(); ++it) {
    ll x = it->first;
    vector<int> hs = it->second;

    auto next_it = next(it);
    if (next_it != xs.end() && next_it -> first == x+1) {
      vector<int> next_hs = next_it->second;
      // Sort descending
      sort(next_hs.begin(), next_hs.end(), [&](int a, int b) {
        return houses[a].second > houses[b].second;
      });

      for (size_t j = 0; j < hs.size(); ++j) {
        int h = hs[j];
        int y = houses[h].second;

        // House below
        for (int next_h : next_hs) {
          int next_y = houses[next_h].second;

          if (next_y <= y) {
            edges.push_back({y - next_y, h, next_h});
            break;
          }
        }

        // House above
        int max_y = j < hs.size() - 1 ? houses[hs[j+1]].second : INT_MAX;
        for (int next_h : next_hs) {
          int next_y = houses[next_h].second;
          if (next_y <= y) break;
          if (next_y < max_y - 1) {
            edges.push_back({next_y - y, h, next_h});
          }
        }
      }
    }
  }

  sort(edges.begin(), edges.end());

  DSU dsu(n);
  ll result = LLONG_MAX;

  for (const auto &[c, u, v] : edges) {
    // cerr << c << " " << u << " " << v << "\n";

    dsu.unite(u, v);
    if (dsu.find(0) == dsu.find(n-1)) {
      result = c;
      break;
    }
  }

  if (result >= k || dsu.find(0) != dsu.find(n-1)) {
    cout << "NATT" << "\n";
  } else {
    cout << result << "\n";
  }
}
