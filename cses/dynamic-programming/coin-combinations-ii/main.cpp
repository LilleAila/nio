#include <iostream>
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

  vector<long long> dp(x+1, 0);
  dp[0] = 1;

  for (const int &c : coins) {
    for (int i = 1; i <= x; i++) {
      if (i < c) continue;
      dp[i] = (dp[i] + dp[i-c]) % 1000000007;
    }
  }

  cout << dp[x] << endl;
}
