// Too slow
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string INF = {'Z' + 1};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<char>> grid(n, vector<char>(n));

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < n; ++j) {
      grid[i][j] = s[j];
    }
  }

  vector<string> dp0(n, INF);
  vector<string> dp1;
  dp0[0] = "";
  for (int i = 0; i < n; ++i) {
    dp1.assign(n, INF);
    for (int j = 0; j < n; ++j) {
      if (i > 0)
        dp1[j] = min(dp1[j], dp0[j] + grid[i][j]);
      if (j > 0)
        dp1[j] = min(dp1[j], dp1[j - 1] + grid[i][j]);
    }
    swap(dp0, dp1);
  }

  cout << dp0[n - 1] << endl;
}
