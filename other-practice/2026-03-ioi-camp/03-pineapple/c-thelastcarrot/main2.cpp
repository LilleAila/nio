#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using ll = long long;

int n, m, k;

ll combinations(int n, int target) {
  ll result = 0;
  for (int i = 1; i <= m; ++i) {
    result += combinations(n-1, target-i);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  cin >> n >> m >> k;

  int total_combinations = pow(m, n);
  int min_sum = n;
  int max_sum = n * m;
  int peak = (min_sum + max_sum) / 2;

  // dp[n][k] where n is the number of dice and k is the sum
  vector<vector<ll>> dp(n+1, vector<ll>(max_sum + 1, 0));
  for (int i = 1; i <= n; ++i) dp[i][1] = 1;
  for (int j = 1; j <= max_sum; ++j) dp[1][j] = 1;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= max_sum; ++j) {
      for (int x = 1; x < m; ++x) {
        dp[i][j] += dp[i-1][j-x];
      }
    }
  }

  cerr << dp[2][4] << "\n";
}
