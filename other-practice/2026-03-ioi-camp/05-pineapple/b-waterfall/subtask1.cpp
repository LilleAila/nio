#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c;
  cin >> r >> c;

  int k, n;
  cin >> k >> n;

  vector<bool> dp0(c, false);
  vector<bool> dp1(c, false);

  for (int i = 0; i < k; ++i) {
    int v;
    cin >> v;
    dp1[v] = true;
  }

  set<pair<int, int>> cliff;
  for (int i = 0; i < n; ++i) {
    int y, x;
    cin >> y >> x;
    cliff.insert({y, x});
  }

  for (int y = r-1; y >= 0; --y) {
    swap(dp0, dp1);
    fill(dp1.begin(), dp1.end(), false);

    for (int x = 0; x < c; ++x) {
      dp1[x] = (dp0[x] && cliff.find({y, x}) == cliff.end());
    }
  }
}
