#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> snow(m, 0);

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < m; ++x) {
      char c;
      cin >> c;
      if (c == 'S') {
        ++snow[x];
      }
    }
  }

  for (int y = 0; y < n; ++y) {
    for (int x = 0; x < m; ++x) {
      if (y >= n - snow[x]) {
        cout << 'S';
      } else {
        cout << '.';
      }
    }
    cout << "\n";
  }
}
