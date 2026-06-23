#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    int m;
    cin >> m;

    vector<pair<int, int>> dolls(m);
    for (int i = 0; i < m; ++i)
      cin >> dolls[i].first >> dolls[i].second;

    sort(dolls.begin(), dolls.end(), [](const auto a, const auto b) {
      // Width ascending, height descending tiebreaker but reversed as the comment below describes
      // - which becomes width descending, height ascending
      return a.first != b.first ? a.first > b.first : a.second < b.second;
    });

    // Finding the number of chains required is according to Dilworth's theorem the same as finding the maximum size of an antichain. In other words, we need to find the longest nonincreasing subsequence. As the width is now sorted, we can ignore it and only look at the height. Instead of changing the logic, the sorting can be inverted, as this then becomes the longest nondecreasing subsequence

    vector<int> dp;
    for (const auto &[_, h] : dolls) {
      auto it = upper_bound(dp.begin(), dp.end(), h);
      if (it == dp.end()) {
        dp.push_back(h);
      } else {
        *it = h;
      }
    }
    cout << dp.size() << "\n";
  }
}
