#include <iostream>
#include <climits>
#include <vector>
#include <utility>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> xs(n);
  vector<vector<int>> positions(k+1);

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    xs[i] = x;
    positions[x].push_back(i);
  }

  int min_dist = INT_MAX;

  for (int u : positions[1]) {
    int dist = 0;
    int x = 1;

    while (x != k) {
      int i = (u + dist) % n;
      if (xs[i] == x + 1) {
        ++x;
      }
      ++dist;
    }

    if (dist < min_dist) {
      min_dist = dist;
    }
  }

  cout << min_dist << "\n";
}
