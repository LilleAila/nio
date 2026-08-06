// N, Q <= 1000
// Can use brute force with one dfs for each query

#include <iostream>
#include <vector>
using namespace std;

const int K = 25;

vector<vector<int>> adj;

bool dfs(int u, int target) {
  if (u == target) return true;
  bool result = false;
  for (int v : adj[u]) {
    if (dfs(v, target)) result = true;;
  }
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  adj.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    // to 0-indexed
    --a;
    --b;
    adj[a].push_back(b);
  }

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    int h, w;
    cin >> h >> w;
    // to 0-indexed
    --h;
    --w;
    cout << (dfs(h, w) ? "ja" : "nej") << "\n";
  }
}
