// https://open.kattis.com/problems/includescoring

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<tuple<int, int, int, int, int>> xs;
  for (int i = 0; i < n; i++) {
    int s, p, f, o;
    cin >> s >> p >> f >> o;
    xs.push_back({i, s, p, f, o});
  }

  array<int, 32> scores = {100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0};
  array<int, 32> scores_prefix;
  partial_sum(scores.begin(), scores.end(), scores_prefix.begin());

  sort(xs.begin(), xs.end(), [](const auto& a, const auto& b) {
    if (get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b); // problems descending
    if (get<2>(a) != get<2>(b)) return get<2>(a) < get<2>(b); // time penalty ascending
    if (get<3>(a) != get<3>(b)) return get<3>(a) < get<3>(b); // submitted ascending
    // fallback to just sort by index if all equal, it doesn't really matter
    return get<0>(a) < get<0>(b);
  });

  int lastRank = 0;
  int nWithRank = 0;
  tuple<int, int, int, int, int> last = {0, 0, 0, 0, 0};
  vector<vector<int>> ranks(31);

  for(const auto& x : xs) {
    if (get<1>(x) == get<1>(last) && get<2>(x) == get<2>(last) && get<3>(x) == get<3>(last)) {
      nWithRank++;
    } else {
      lastRank += nWithRank;
      nWithRank = 1;
    }
    if (lastRank > 30) lastRank = 30;
    ranks[lastRank].push_back(get<0>(x));
    last = x;
  }

  vector<int> result_scores(n);
  for (int i = 0; i < ranks.size(); i++) {
    vector<int> r = ranks[i];
    int nr = r.size();
    if (nr == 0) continue;
    int score = i < 30 ? ((i == 0 ? scores_prefix[i + nr - 1] : scores_prefix[min(i + nr - 1, 29)] - scores_prefix[i-1]) + nr - 1) / nr : 0;
    for (const auto& j : r) {
      int bonus = get<4>(xs[j]);
      result_scores[j] = score + bonus;
    }
  }

  for (const auto& x : result_scores) {
    cout << x << endl;
  }
}
