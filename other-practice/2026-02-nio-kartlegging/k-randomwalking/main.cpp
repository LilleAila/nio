#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (true) {
    int k, n, e;
    cin >> k >> n >> e;
    if (k == 0) break;

    int m = pow(2, n);
    vector<vector<int>> graph(m);

    for (int i = 0; i < e; ++i) {
      int u, v;
      cin >> u >> v;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }
  }
}
