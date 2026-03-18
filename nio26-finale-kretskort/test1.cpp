// NOTE: this does not work because the items are processed in the wrong order.
// For this to be correct, they need to be added to the list in descending order in terms of starting point
// However in this code, i have added them all at the same time. This means that the problem specifies
// a1 < b1 < a2 < b2
// But this code also allows
// a1 < b1 < b2 < a2
// The best solution for this would be to handle each pair in descending order as described, and use a fenwick tree.

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  string line;
  cin >> line;

  vector<int> xs;
  for (char c : line) {
    int i = c - 'a';
    xs.push_back(i);
  }

  vector<vector<int>> indexes(k);
  for (int i = 0; i < xs.size(); i++) {
    int v = xs[i];
    indexes[v].push_back(i);
  }

  vector<pair<int, int>> pairs;
  for (int t = 0; t < indexes.size(); t++) {
    vector<int> is = indexes[t];
    int mid = is.size() / 2;
    for (int i = 0; i < mid; i++) {
      pairs.push_back({is[i], is[mid + i]});
    }
  }

  vector<int> end_nodes(n);
  for (const pair<int, int> p : pairs) {
    end_nodes[p.second] = 1;
  }

  vector<long long> prefix(n + 1);
  prefix[0] = 0;
  for (int i = 1; i < end_nodes.size(); i++) {
    prefix[i] = prefix[i-1] + end_nodes[i];
  }

  long long shorts = 0;
  for (const pair<int, int> p : pairs) {
    long long s = prefix[p.second - 1] - prefix[p.first];
    shorts += s;
    cout << p.first << " " << p.second << " " << s << " " << prefix[p.first] << " " << prefix[p.second - 1] << endl;
  }
  cout << shorts << endl;
}
