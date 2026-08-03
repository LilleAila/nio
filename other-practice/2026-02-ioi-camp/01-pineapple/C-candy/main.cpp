#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  unordered_map<int, int> candies;

  for (int i = 0; i < n; ++i) {
    int k;
    cin >> k;

    for (int j = 0; j < k; ++j) {
      int s, n;
      cin >> s >> n;
      candies[s] += n;
    }
  }

  int maxCandies = 0;
  for (int s = 1; s <= 10; ++s) {
    auto candyIt = candies.find(s);
    int candy = candyIt != candies.end() ? (*candyIt).second : 0;
    auto anticandyIt = candies.find(-s);
    int anticandy = anticandyIt != candies.end() ? (*anticandyIt).second : 0;

    maxCandies += max(candy, anticandy);
  }

  cout << maxCandies << endl;
}
