#include <iostream>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

const int N = 1e5 + 1;
const int M = 2 * N;
bool edge_used[M];

vector<pair<int, int>> adj[N];
vector<int> path;
size_t head[N];

void find_cycle(int u) {
  for (; head[u] < adj[u].size(); head[u]++) {
    auto [v, i] = adj[u][head[u]];
    if (edge_used[i])
      continue;
    edge_used[i] = true;
    find_cycle(v);
  }
  path.push_back(u);
}

void find_cycle2(int u) {
  stack<int> s;
  s.push(u);

  while (!s.empty()) {
    int u = s.top();

    if (head[u] < adj[u].size()) {
      auto [v, i] = adj[u][head[u]];
      ++head[u];

      if (!edge_used[i]) {
        edge_used[i] = true;
        s.push(v);
      }
    } else {
      path.push_back(u);
      s.pop();
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back({b, i});
    adj[b].push_back({a, i});
  }

  for (int i = 1; i <= n; ++i) {
    if (adj[i].size() % 2 != 0) {
      cout << "IMPOSSIBLE" << "\n";
      return 0;
    }
  }

  find_cycle2(1);

  if (path.size() != (size_t)m + 1) {
    cout << "IMPOSSIBLE" << "\n";
    return 0;
  }

  for (int i : path)
    cout << i << " ";
  cout << "\n";
}
