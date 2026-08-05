#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n, k, r;
  cin >> n >> k >> r;

  vector<int> present(k, 0);

  vector<int> xs(n);
  for (int i = 0; i < n; ++i) {
    cin >> xs[i];
    ++present[xs[i]];
  }

  vector<int> required(k, 0);
  for (int i = 0; i < n; ++i) {
    int b, q;
    cin >> b >> q;
    required[b] = q;
  }

  for (int i = 0; i < k; ++i) {
    if (present[i] < required[i]) {
      cout << "impossible" << "\n";
      return 0;
    }
  }

  int min_length = n;
  int a = 0;
  int b = n-1;

  // Find first valid b
  while (true) {
    int x = xs[b];
    // cerr << x << " " << present[x] << " " << required[x] << endl;
    if (present[x]-1 < required[x]) break;
    --present[x];
    --b;
  }
  // Find minimum a for first b
  while (present[xs[a]] > required[xs[a]]) {
    --present[xs[a]];
    ++a;
  }

  min_length = b - a + 1;

  // cerr << a << " " << b << "\n";

  // Two pointers, find minimum valid substring
  while (++b < n) {
    // cerr << a << " " << b << "\n";
    ++present[xs[b]];

    while (present[xs[a]] > required[xs[a]]) {
      --present[xs[a]];
      ++a;
    }
    min_length = min(min_length, b - a + 1);
  }

  cout << min_length << "\n";
}
