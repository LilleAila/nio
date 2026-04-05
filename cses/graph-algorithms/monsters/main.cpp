#include <climits>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

const int MAXN = 1001, MAXM = 10001;
int n, m;
bool wall[MAXN * MAXM];

vector<pair<int, char>> neighbors(int u) {
  vector<pair<int, char>> vs;
  vs.reserve(4);
  if (u >= m)
    vs.push_back({u - m, 'U'});
  if (u < n * m - m)
    vs.push_back({u + m, 'D'});
  if (u % m > 0)
    vs.push_back({u - 1, 'L'});
  if (u % m < m - 1)
    vs.push_back({u + 1, 'R'});
  return vs;
}

bool boundary(int u) {
  return u < m || u > n * m - m || u % m == 0 || u % m == m - 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  vector<int> monster;
  int start = 0;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;

    for (int j = 0; j < m; ++j) {
      if (s[j] == '#')
        wall[i * m + j] = true;
      else if (s[j] == 'A')
        start = i * m + j;
      else if (s[j] == 'M')
        monster.push_back(i * m + j);
    }
  }

  queue<int> q;
  vector<int> monster_dist(m * n, INT_MAX);
  for (int i : monster) {
    q.push(i);
    monster_dist[i] = 0;
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto &[v, _] : neighbors(u)) {
      int new_dist = monster_dist[u] + 1;
      if (!wall[v] && new_dist < monster_dist[v]) {
        monster_dist[v] = new_dist;
        q.push(v);
      }
    }
  }

  vector<int> dist(m * n, INT_MAX);
  vector<char> visited_direction(m * n);
  vector<int> visited_from(m * n);
  dist[start] = 0;
  q.push(start);
  while (!q.empty()) {
    int u = q.front();
    q.pop();

    if (boundary(u)) {
      cout << "YES" << endl;
      deque<char> path;
      for (int i = u; i != start; i = visited_from[i]) {
        path.push_front(visited_direction[i]);
      }
      cout << path.size() << endl;
      for (char i : path)
        cout << i;
      cout << "\n";
      return 0;
    }

    for (auto &[v, d] : neighbors(u)) {
      if (wall[v])
        continue;
      int new_dist = dist[u] + 1;
      if (new_dist < dist[v] && new_dist < monster_dist[v]) {
        dist[v] = new_dist;
        visited_direction[v] = d;
        visited_from[v] = u;
        q.push(v);
      }
    }
  }

  cout << "NO" << "\n";
}
