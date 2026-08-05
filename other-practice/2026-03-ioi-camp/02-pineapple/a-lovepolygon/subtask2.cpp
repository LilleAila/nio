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

  vector<int> adj(n);
  for (const auto &[u, v] : adj_strings) {
    int x = string_to_index[u];
    int y = string_to_index[v];
    adj[x] = y;
  }

  vector<bool> visited(n, false);
  int result = 0;
  int unpaired = 0;
  for (int i = 0; i < n; ++i) {
    if (visited[i]) continue;
    visited[i] = true;
    int length = 1;
    for (int v = adj[i]; v != i; v = adj[v]) {
      ++length;
      visited[v] = true;
    }
    result += length / 2;
    unpaired += length % 2;
  }

  result += unpaired;

  cerr << result << "\n";
}
