#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<long long> xs(n);
  for (long long i = 0; i < n; i++) {
    long long x;
    cin >> x;
    xs[i] = x;
  }

  vector<long long> prefix(n + 1);
  partial_sum(xs.begin(), xs.end(), prefix.begin() + 1);

  for (int i = 0; i < q; i++) {
    int a, b;
    cin >> a >> b;
    long long result = prefix[b] - prefix[a - 1];
    cout << result << endl;
  }
}
