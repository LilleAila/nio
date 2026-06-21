#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <utility>
#include <queue>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  while (n--) {
    int s;
    cin >> s;

    priority_queue<pair<int, int>> pq;

    for (int i = 0; i < s; ++i) {
      int x, y;
      cin >> x >> y;
      pq.push({x, y});
    }

    int h = 0;
    double total_length = 0.0;
    auto prev = pq.top();
    pq.pop();

    while (!pq.empty()) {
      auto next = pq.top();
      pq.pop();

      const auto &[x1, y1] = next;
      const auto &[x2, y2] = prev;

      if (next.second > h) {
        double dx = x2 - x1;
        double dy = y2 - y1;
        double x = dx * (h - y1) / dy + x1;

        double l = sqrt(pow(x - x1, 2) + pow(y1 - h, 2));

        total_length += l;
      }

      h = max(h, y1);
      prev = next;
    }

    // double result = round(total_length * 100.0) / 100.0;
    cout << fixed << setprecision(2) << total_length << "\n";
  }
}
