#include <iostream>
#include <vector>
#include <climits>
using namespace std;
using ll = long long;

const ll INF = LLONG_MAX;

const int MAXN = 1e5 + 1;
const int MAXM = 1e1 + 1;
const int MAXK = 1e5 + 1;

bool work[MAXK];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> visits(n);
  for (int i = 0; i < n; ++i)
    cin >> visits[i];

  vector<int> duration(m);
  for (int i = 0; i < m; ++i)
    cin >> duration[i];

  vector<int> price(m);
  for (int i = 0; i < m; ++i)
    cin >> price[i];

  for (int i = 0; i < k; ++i) {
    int r;
    cin >> r;
    work[r] = true;
  }

  vector<ll> dp(n+1, INF);
  dp[0] = 0;

  // dp[i] = cheapest cost for the first i visits.
}
