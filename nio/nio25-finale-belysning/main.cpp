#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> ys(n);
  for (int i = 0; i < n; i++) {
    int y;
    cin >> y;
    ys[i] = y;
  }

  vector<vector<int>> lys(n, vector<int>(n));
  for (int a = 0; a < n; a++) {
    for (int b = a; b < n; b++) {
      int dy = INT_MAX;
      for (int lx = a; lx <= b; lx++) {
        int ly = 0;
        for (int i = a; i <= b; i++) {
          int cly = abs(lx - i) + ys[i];
          ly = max(ly, cly);
        }
        dy = min(dy, ly - ys[lx]);
      }
      lys[a][b] = dy;
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;

    vector<int> dp(n, INT_MAX / 2);

    for (int j = 0; j < n; j++) {
      for (int i = 0; i <= j; i++) {
        int c = a + b * lys[i][j];
        int prev = i == 0 ? 0 : dp[i - 1];
        dp[j] = min(dp[j], prev + c);
      }
    }

    cout << dp[n - 1] << endl;
  }
}
