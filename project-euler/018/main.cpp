#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<vector<int>> nodes;

  string line;
  while (getline(cin, line)) {
    stringstream ss(line);

    vector<int> xs;
    int x;
    while (ss >> x) {
      xs.push_back(x);
    }

    nodes.push_back(xs);
  }

  // for (const auto &xs : nodes) {
  //   cout << "[ ";
  //   for (const auto &x : xs)
  //     cout << x << " ";
  //   cout << "]" << endl;
  // }

  int h = nodes.size();
  int n = h * (h + 1) / 2;

  vector<vector<pair<int, int>>> graph(n + 1);
  for (int y = 0; y < h - 1; y++) {
    auto &row = nodes[y];
    int w = row.size();
    for (int x = 0; x < w; x++) {
      int weight = row[x];
      int node_id = y * (y + 1) / 2 + x;
      int n1 = (y + 1) * (y + 2) / 2 + x;
      int n2 = (y + 1) * (y + 2) / 2 + x + 1;
      // cout << node_id << " " << n1 << " " << n2 << endl;
      graph[node_id].push_back({weight, n1});
      graph[node_id].push_back({weight, n2});
    }
  }

  int y = h - 1;
  for (int x = 0; x < h; x++) {
    int node_id = y * (y + 1) / 2 + x;
    int weight = nodes[y][x];
    graph[node_id].push_back({weight, n});
    // cout << node_id << endl;
  }

  priority_queue<pair<int, int>> pq;
  vector<int> dist(n + 1, 0);
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [d, a] = pq.top();
    pq.pop();

    if (d < dist[a])
      continue;

    for (auto &[weight, b] : graph[a]) {
      int new_cost = d + weight;
      if (new_cost > dist[b]) {
        dist[b] = new_cost;
        pq.push({dist[b], b});
      }
    }
  }

  cout << dist[n] << endl;
}
