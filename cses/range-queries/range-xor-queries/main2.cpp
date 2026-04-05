#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> xs(n);
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    xs[i] = x;
  }

  vector<int> prefix(n + 1);
  for (int i = 1; i <= n; ++i) {
    prefix[i] = prefix[i - 1] ^ xs[i - 1];
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    int result = prefix[b] ^ prefix[a - 1];
    cout << result << endl;
    ;
  }
}
