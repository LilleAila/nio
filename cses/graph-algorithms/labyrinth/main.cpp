#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  int a = 0;
  int b = 0;
  vector<bool> grid(n * m);

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;

    for (int j = 0; j < m; j++) {
      char c = s[j];
      int idx = i * m + j;
      grid[idx] = c != '#';
      if (c == 'A')
        a = idx;
      else if (c == 'B')
        b = idx;
    }
  }

  vector<char> dir(n * m, 0);

  vector<bool> visited(n * m);
  queue<tuple<int, int>> q;
  q.push({a, 0});
  visited[a] = true;

  while (!q.empty()) {
    auto [u, length] = q.front();
    q.pop();

    if (u == b) {
      cout << "YES" << endl;
      cout << length << endl;
      int node = b;
      string path = "";
      while (node != a) {
        char d = dir[node];
        path += d;
        if (d == 'U')
          node += m;
        else if (d == 'D')
          node -= m;
        else if (d == 'L')
          node += 1;
        else if (d == 'R')
          node -= 1;
      }
      reverse(path.begin(), path.end());
      cout << path << endl;
      return 0;
    }

    if (u >= m) {
      int next = u - m;
      if (!visited[next] && grid[next]) {
        visited[next] = true;
        dir[next] = 'U';
        q.push({next, length + 1});
      }
    }
    if (u < n * m - m) {
      int next = u + m;
      if (!visited[next] && grid[next]) {
        visited[next] = true;
        dir[next] = 'D';
        q.push({next, length + 1});
      }
    }
    if (u % m > 0) {
      int next = u - 1;
      if (!visited[next] && grid[next]) {
        visited[next] = true;
        dir[next] = 'L';
        q.push({next, length + 1});
      }
    }
    if (u % m < m - 1) {
      int next = u + 1;
      if (!visited[next] && grid[next]) {
        visited[next] = true;
        dir[next] = 'R';
        q.push({next, length + 1});
      }
    }
  }

  cout << "NO" << endl;
}
