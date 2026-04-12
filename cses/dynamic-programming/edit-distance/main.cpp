#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b;
  cin >> a >> b;

  int n = a.size();
  int m = b.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1));

  // String to empty
  for (int i = 0; i <= n; ++i)
    dp[i][0] = i;
  // Empty to string
  for (int i = 0; i <= m; ++i)
    dp[0][i] = i;

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      dp[i][j] = min({
          dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]), // Replace / Keep
          dp[i][j - 1] + 1,                          // Insert
          dp[i - 1][j] + 1                           // Delete
      });
    }
  }

  cout << dp[n][m] << "\n";
}
