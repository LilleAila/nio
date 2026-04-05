#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 2e5 + 1;
vector<int> adj[MAXN];

array<int, 2> dfs(int u, int p) {
  array<int, 2> dp = {0, 0};
  for (int v : adj[u]) {
    if (v == p)
      continue;
    array<int, 2> child_dp = dfs(v, u);
    dp[1] = max({dp[0] + child_dp[0] + 1,   // Pair u and v with each other
                 dp[1] + child_dp[1],       // Pair u and v separately
                 dp[1] + child_dp[0]});     // Skip v, pair u separately
    dp[0] += max(child_dp[0], child_dp[1]); // Skip u, pair v separately
  }
  return dp;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  auto dp = dfs(1, 1);
  cout << max(dp[0], dp[1]) << endl;
}
