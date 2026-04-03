#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, x;
  cin >> n >> x;

  vector<pair<int, int>> books(n);

  for (int i = 0; i < n; i++) {
    int h;
    cin >> h;
    books[i].first = h;
  }

  for (int i = 0; i < n; i++) {
    int s;
    cin >> s;
    books[i].second = s;
  }

  // This is basically knapsack where the weight is the price and the value is
  // the number of pages.

  vector<int> dp(x + 1, 0);
  for (int i = 0; i < n; ++i) {
    auto [price, pages] = books[i];
    for (int p = x; p >= price; --p) {
      dp[p] = max(dp[p], dp[p - price] + pages);
    }
  }

  cout << dp[x] << endl;
}
