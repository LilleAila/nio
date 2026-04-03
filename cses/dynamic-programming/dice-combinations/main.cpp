#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> dp(n+1, 0);
  dp[0] = 1;

  for (int i = 1; i <= n; i++) {
    for (int k = 1; k <= 6; k++) {
      if (i >= k) dp[i] = (dp[i] + dp[i-k]) % 1000000007;
    }
  }

  cout << dp[n] << endl;
}
