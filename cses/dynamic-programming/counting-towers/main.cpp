#include <array>
#include <iostream>
using namespace std;
using ll = long long;

const int N = 1e6;
array<ll, 2> dp[N + 2] = {0};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  dp[1][0] = 1;
  dp[1][1] = 1;
  for (int i = 2; i <= N; ++i) {
    dp[i][0] = (dp[i - 1][0] * 4 + dp[i - 1][1]) % 1000000007;
    dp[i][1] = (dp[i - 1][0] + dp[i - 1][1] * 2) % 1000000007;
  }

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    cout << (dp[n][0] + dp[n][1]) % 1000000007 << "\n";
  }
}
