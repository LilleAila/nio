#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> dp(n + 1, INT_MAX / 2);
  dp[n] = 0;

  for (int i = n; i > 0; i--) {
    string s = to_string(i);

    for (char c : s) {
      int d = c - '0';

      dp[i - d] = min(dp[i - d], dp[i] + 1);
    }
  }

  cout << dp[0] << endl;
}
