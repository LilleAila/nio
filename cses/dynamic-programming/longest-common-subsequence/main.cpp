#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int N = 1005;
int dp[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> as(n);
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    as[i] = a;
  }

  vector<int> bs(m);
  for (int i = 0; i < m; ++i) {
    int b;
    cin >> b;
    bs[i] = b;
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (as[i - 1] == bs[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  cout << dp[n][m] << "\n";

  vector<int> lcs;
  int i = n, j = m;
  while (i > 0 && j > 0) {
    if (as[i - 1] == bs[j - 1]) {
      lcs.push_back(as[i - 1]);
      --i;
      --j;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      --i;
    } else {
      j--;
    }
  }
  reverse(lcs.begin(), lcs.end());
  for (int x : lcs)
    cout << x << " ";
  cout << "\n";
}
