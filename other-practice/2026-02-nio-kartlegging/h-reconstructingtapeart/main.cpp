#include <iostream>
#include <tuple>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  vector<tuple<int, int, int>> intervals(n, {INT_MAX, 0, 0});

  for (int i = 1; i <= n; ++i) {
    int c;
    cin >> c;
    int j = c - 1;
    get<0>(intervals[j]) = min(get<0>(intervals[j]), i);
    get<1>(intervals[j]) = max(get<1>(intervals[j]), i);
    get<2>(intervals[j]) = c;
  }

  intervals.erase(remove_if(intervals.begin(), intervals.end(), [](const auto &i) { return get<2>(i) == 0; }), intervals.end());
  sort(intervals.begin(), intervals.end());

  int end = 0;
  for (const auto &[a, b, c] : intervals) {
    if (a > end) {
      end = b;
    } else {
      if (b > end) {
        cout << "IMPOSSIBLE" << "\n";
        return 0;
      }
    }
  }

  cout << intervals.size() << "\n";
  for (const auto &[a, b, c] : intervals) {
    cout << a << " " << b << " " << c << "\n";
  }
}
