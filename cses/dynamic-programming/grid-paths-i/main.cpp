#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<bool> grid(n * n);

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;

    for (int j = 0; j < n; j++) {
      grid[i * n + j] = s[j] == '.';
    }
  }

  vector<int> dp(n * n, 0);
  dp[0] = grid[0];
  for (int i = 0; i < n * n; i++) {
    if (i % n > 0) {
      dp[i] = (dp[i] + dp[i - 1] * grid[i]) % 1000000007;
    }
    if (i >= n) {
      dp[i] = (dp[i] + dp[i - n] * grid[i]) % 1000000007;
    }
  }

  cout << dp[n * n - 1] << endl;
}
