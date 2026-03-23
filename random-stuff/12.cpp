#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;

int main() {
  int n = 5;
  vector<vector<pair<int, int>>> graph(n);
  graph[0].push_back({1, 4});
  graph[0].push_back({2, 1});
  graph[2].push_back({1, 2});
  graph[1].push_back({3, 1});

  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;

  vector<int> dist(n, INF);
  dist[0] = 0;
  pq.push({0, 0});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > dist[u])
      continue;

    for (auto &[v, weight] : graph[u]) {
      int new_cost = d + weight;
      if (new_cost < dist[v]) {
        dist[v] = new_cost;
        pq.push({dist[v], v});
      }
    }
  }

  cerr << "[ ";
  for (int &i : dist)
    cerr << i << " ";
  cerr << "]" << endl;
}
