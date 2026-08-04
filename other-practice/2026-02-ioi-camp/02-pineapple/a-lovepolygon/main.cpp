#include <iostream>
#include <climits>
#include <vector>
#include <utility>
#include <unordered_map>
using namespace std;

unordered_map<string, string> adj;

int f(vector<string> xs) {
  if (xs.size() < 2) return 0;
  int min = INT_MAX;

  vector<string> min_xs;
  for (size_t i = 1; i < xs.size(); ++i) {
    bool ab = adj.at(xs[i]) == xs[0];
    bool ba = adj.at(xs[0]) == xs[i];

    vector<string> new_xs;
    for (size_t j = 1; j < xs.size(); ++j) {
      if (j != i) new_xs.push_back(xs[j]);
    }

    int result = !ab + !ba + f(new_xs);
    if (result < min) {
      min = result;
      min_xs = new_xs;
    }
  }

  return min;
}

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

  for (int i = 0; i < n; ++i) {
    string u, v;
    cin >> u >> v;
    adj[u] = v;
  }

  vector<string> xs;
  for (const auto &[u, v] : adj) {
    // cerr << u << " " << v << "\n";
    xs.push_back(u);
  }

  cout << f(xs) << "\n";
}
