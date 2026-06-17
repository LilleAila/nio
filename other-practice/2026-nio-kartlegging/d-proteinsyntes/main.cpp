#include <iostream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

const int INF = INT_MAX;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  string t;
  cin >> t;

  int m;
  cin >> m;

  vector<string> strings(m);
  for (int i = 0; i < m; ++i)
    cin >> strings[i];

  vector<int> dp(n+1, INF);
  dp[0] = 0;

  for (int i = 0; i < n; ++i) {
    if (dp[i] == INF) continue;

    for (const string& s : strings) {
      int l = s.length();
      if (i + l <= n && t.compare(i, l, s) == 0) {
        dp[i+l] = min(dp[i+l], dp[i] + 1);
      }
    }
  }

  cout << dp[n] << "\n";
}
