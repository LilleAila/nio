#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<bool> grid(n * m, false);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < m; ++j) {
      grid[i * m + j] = s[j] == '.';
    }
  }

  int rooms = 0;
  vector<bool> visited(n * m, false);

  for (int a = 0; a < n * m; ++a) {
    if (visited[a] || !grid[a])
      continue;

    ++rooms;

    queue<int> q;
    q.push(a);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      if (visited[u] || !grid[u])
        continue;
      visited[u] = true;

      if (u >= m)
        q.push(u - m);
      if (u < n * m - m)
        q.push(u + m);
      if (u % m > 0)
        q.push(u - 1);
      if (u % m < m - 1)
        q.push(u + 1);
    }
  }

  cout << rooms << endl;
}
