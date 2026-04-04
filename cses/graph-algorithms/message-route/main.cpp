#include <deque>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);
  while (m--) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> visited(n + 1, 0);
  queue<int> q;
  q.push(1);
  visited[1] = 1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (u == n)
      break;

    for (int v : adj[u]) {
      if (visited[v] > 0)
        continue;
      visited[v] = u;
      q.push(v);
    }
  }

  if (visited[n] == 0) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }

  deque<int> path = {};
  for (int i = n; i != 1; i = visited[i]) {
    path.push_front(i);
  }
  path.push_front(1);
  cout << path.size() << endl;
  for (int i : path)
    cout << i << " ";
  cout << endl;
}
