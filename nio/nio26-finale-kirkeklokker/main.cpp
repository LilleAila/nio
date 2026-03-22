// This code is so slow that it is realistically not feasible
// the real only solution would be a brute force with some optimizations to prefer smaller numbers

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n = 49;
  vector<array<int, 4>> sequences;

  for (int sum = 0; sequences.size() < n; sum++) {
    for (int a = 1; a <= sum; a++) {
      for (int b = 1; b <= sum - a; b++) {
        for (int c = 1; c < sum - a - b; c++) {
          int d = sum - a - b - c;

          array<int,4> xs = {a, b, c, d};
          sequences.push_back(xs);
          if (sequences.size() == n) break;
        }
        if (sequences.size() == n) break;
      }
      if (sequences.size() == n) break;
    }
  }

  vector<vector<int>> graph(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      bool valid = true;
      for (int k = 0; k < 3; k++) {
        if (sequences[i][k+1] == sequences[j][k]) valid = false;
      }
      if (valid) {
        graph[i].push_back(j);
      }
    }
  }

  for (int start = 0; start < n; start++) {
    vector<int> path;

    stack<tuple<int, vector<int>, long long>> st;
    vector<bool> visited_init(n, false);
    st.push({ start, { start }, 1LL << start });

    while (!st.empty()) {
      auto [node, path, visited] = st.top();
      st.pop();

      if (path.size() == n) {
        for (int i : path) {
          int a = sequences[i][0];
          cout << a << " ";
        }
        auto end_sequences = sequences[path[n-1]];
        cout << end_sequences[1] << " " << end_sequences[2] << " " << end_sequences[3];
        return 0;
      }

      for (int x : graph[node]) {
        if (!(visited & (1LL << x))) {
          auto new_path = path;
          new_path.push_back(x);
          st.push({ x, new_path, visited | (1LL << x) });
        }
      }
    }
  }
}
