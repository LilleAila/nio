#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

const int MAXN = 1e5 + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<ll> xs(n);
  for (int i = 0; i < n; ++i) {
    ll x;
    cin >> x;
    xs[i] = x;
  }

  vector<ll> last(m + 2, 0);
  vector<ll> current(m + 2, 0);

  if (xs[0] == 0) {
    for (int i = 1; i <= m; ++i)
      last[i] = 1;
  } else {
    last[xs[0]] = 1;
  }

  for (int i = 1; i < n; ++i) {
    fill(current.begin(), current.end(), 0);
    ll x = xs[i];

    if (x == 0) {
      for (int j = 1; j <= m; ++j) {
        current[j] = (last[j - 1] + last[j] + last[j + 1]) % 1000000007;
      }
    } else {
      current[x] = (last[x - 1] + last[x] + last[x + 1]) % 1000000007;
    }

    swap(last, current);
  }

  ll result = 0;
  for (ll i : last)
    result = (result + i) % 1000000007;
  cout << result << endl;
}
