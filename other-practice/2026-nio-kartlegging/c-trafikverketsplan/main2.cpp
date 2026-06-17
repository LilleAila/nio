#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 3e5 + 1;
vector<int> adj_rev[MAXN];
bool visited[MAXN];

void dfs(int u) {
  visited[u] = true;
  for (int v : adj_rev[u]) {
    // cerr << v << endl;
    if (!visited[v]) {
      dfs(v);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    adj_rev[b].push_back(a);
  }

  int q;
  cin >> q;

  dfs(1);

  while (q--) {
    int h, w;
    cin >> h >> w;
    if (visited[h]) {
      cout << "ja" << "\n";
    } else {
      cout << "nej" << "\n";
    }
  }
}
