#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k, b;
  cin >> n >> m >> k >> b;

  vector<pair<ll, int>> questions(n);
  for (int i = 0; i < n; ++i) {
    ll p;
    int c;
    cin >> p >> c;
    --c;
    questions[i] = {p, c};
  }

  if (m == 1) {
    sort(questions.begin(), questions.end(), greater<pair<ll, int>>());
    ll score = 0;
    for (int i = 0; i < k; ++i) {
      score += questions[i].first;
    }
    if (k >= n) score += b;
    cout << score << "\n";
    return 0;
  }

  sort(questions.begin(), questions.end(), [](const pair<ll, int> &a, const pair<ll, int> &b) {
    if (a.second == b.second) return a.first > b.first;
    return a.second > b.second;
  });

  vector<vector<ll>> categories(m);
  for (const auto &[p, c] : questions) {
    categories[c].push_back(p);
  }

  sort(categories.begin(), categories.end(), [](const vector<ll> &a, const vector<ll> &b) {
    return a.size() < b.size();
  });

  // for (const auto &x : categories) {
  //   for (const auto &y : x) {
  //     cerr << y << " ";
  //   }
  //   cerr << endl;
  // }

  ll score = 0;
  size_t c = 0, i = 0;
  int answered = 0;
  while (true) {
    score += categories[c][i];
    ++i;
    if (i >= categories[c].size()) {
      i = 0;
      ++c;
      score += b;
    }

    ++answered;
    if (answered >= k) break;
  }

  cout << score << endl;
}
