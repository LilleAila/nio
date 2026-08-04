// Subtask 3: There are no relationships or "love polygons"
// This essentially means that it can be represented as a DAG
// Then, i believe it would be possible to use a topological sort
// and then traverse the tree to create relationships
//
// For the full solution, i believe i would have to first use kosaraju
// to remove cycles and turn it into a DAG, then use this solution

#include <iostream>
#include <climits>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n;
  cin >> n;

  if (n % 2 != 0) {
    cout << "-1" << "\n";
    return 0;
  }

  map<string, string> adj_strings;
  for (int i = 0; i < n; ++i) {
    string u, v;
    cin >> u >> v;
    adj_strings[u] = v;
  }

  int i = 0;
  unordered_map<string, int> string_to_index;
  for (const auto &[u, v] : adj_strings) {
    string_to_index[u] = i++;
    // cerr << "(" << u << ", " << i-1 << ")\n";
  }

  vector<int> in_degree(n, 0);
  vector<int> adj(n, -1);
  for (const auto &[u, v] : adj_strings) {
    int x = string_to_index[u];
    int y = string_to_index[v];
    adj[x] = y;
    ++in_degree[y];
  }

  queue<int> q;
  for (int i = 0; i < n; ++i) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }

  vector<bool> paired(n, false);
  int result = 0;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    // Mark this node as processed, thus reducing the next node's in-degree
    int v = adj[u];
    --in_degree[v];

    // Connect the next node to this node
    if (!paired[v]) {
      paired[u] = true;
      paired[v] = true;

      --in_degree[adj[v]];
      adj[v] = u;
      ++result;

      if (in_degree[v] == 0) {
        q.push(v);
      }

      // cerr << u << " " << v << endl;
    }
  }

  int unpaired = 0;
  for (bool p : paired) if (!p) ++unpaired;
  result += unpaired / 2;

  cout << result << "\n";
}
