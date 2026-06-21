#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX;

int main() {
  ios::sync_with_stdio(false),
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;

  int k, r;
  cin >> k >> r;

  vector<int> ls(n);
  for (int i = 0; i < n; ++i)
    cin >> ls[i];

  vector<pair<int, int>> curves(n-1);
  for (int i = 0; i < n - 1; ++i)
    cin >> curves[i].first >> curves[i].second;

  // dp[i][j] is the minimum cost to be at the end of straightaway i in lane j (both 0-indexed)
  vector<vector<ll>> dp(n, vector<ll>(m, INF));

  for (int i = 0; i < m; ++i) {
    ll forward = ls[0];
    if (k * i > forward) continue;
    ll total_cost = forward + r * i;
    dp[0][i] = min(dp[0][i], total_cost);
  }

  for (int i = 1; i < n; ++i) {
    ll forward = ls[i];
    const auto &[s, c] = curves[i-1];
    for (int a = 0; a < m; ++a) {
      if (dp[i-1][a] == INF) continue;

      for (int b = 0; b < m; ++b) {
        ll delta = abs(a - b);
        if (k * delta > forward) continue;
        ll straightaway_cost = forward + r * delta;
        ll curve_cost = s + c * (a + 1); // +1 because 1-indexed
        ll total_cost = straightaway_cost + curve_cost;
        dp[i][b] = min(dp[i][b], dp[i-1][a] + total_cost);
      }
    }
  }

  cout << dp[n-1][0] << "\n";
}
