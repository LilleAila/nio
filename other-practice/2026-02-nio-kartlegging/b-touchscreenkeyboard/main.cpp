#include <iostream>
#include <functional>
#include <queue>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

int manhattan(pair<int, int> p1, pair<int, int> p2) {
  const auto &[x1, y1] = p1;
  const auto &[x2, y2] = p2;
  return abs(x2 - x1) + abs(y2 - y1);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  vector<pair<int, int>> kb('z');
  string row0 = "qwertyuiop";
  for (size_t i = 0; i < row0.size(); ++i) kb[row0[i]] = {i, 0};
  string row1 = "asdfghjkl";
  for (size_t i = 0; i < row1.size(); ++i) kb[row1[i]] = {i, 1};
  string row2 = "zxcvbnm";
  for (size_t i = 0; i < row2.size(); ++i) kb[row2[i]] = {i, 2};

  int t;
  cin >> t;

  while (t--) {
    string s;
    int l;
    cin >> s >> l;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    while (l--) {
      string x;
      cin >> x;

      int dist = 0;

      for (size_t i = 0; i < s.size(); ++i) {
        dist += manhattan(kb[s[i]], kb[x[i]]);
      }

      pq.push({dist, x});
    }

    while (!pq.empty()) {
      auto [d, s] = pq.top();
      pq.pop();

      cout << s << " " << d << "\n";
    }
  }
}
