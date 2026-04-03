#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, x;
  cin >> n >> x;

  vector<int> coins(n);
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c;
    coins[i] = c;
  }
  sort(coins.begin(), coins.end());

  const long long INF = LLONG_MAX / 3;
  vector<long long> dp(x+1, INF);
  dp[0] = 0;
  for (long long i = 0; i <= x; i++) {
    for (const auto &c : coins) {
      if (i < c) break;
      dp[i] = min(dp[i], dp[i-c] + 1);
    }
  }

  if (dp[x] == INF) {
    cout << "-1" << endl;
  } else {
    cout << dp[x] << endl;
  }
}
