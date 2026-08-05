#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <algorithm>
using ll = long long;
using namespace std;

int n, m, k;

vector<vector<double>> memo;

double combinations(int target, int depth) {
  if (memo[depth][target] != -1) return memo[depth][target];
  if (depth <= 0) return target == 0 ? 1 : 0;
  double total_combinations = 0;
  if (target < depth || target > depth * m) return 0;
  int max_dice_value = min(m, target - depth + 1);
  if (max_dice_value < 1) return 0;
  for (int i = 1; i <= max_dice_value; ++i) {
    total_combinations += combinations(target - i, depth - 1);
  }
  memo[depth][target] = total_combinations;
  return total_combinations;
}

double combinations_range(int target_lower, int target_upper, int depth) {
  if (depth <= 0) return target_lower <= 0 && target_upper >= 0 ? 1.0 : 0.0;
  if (target_upper < depth || target_lower > depth * m) return 0.0;
  double total_combinations = 0;
  for (int i = 1; i <= m; ++i) {
    total_combinations += combinations_range(target_lower - i, target_upper - i, depth - 1);
  }
  return total_combinations;
}

// struct SegmentTree {
//   int n;
//   vector<double> tree;
//   void build(vector<double> &xs) {}
// }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  cin >> n >> m >> k;

  double total_combinations = pow(m, n);
  int min_sum = n;
  int max_sum = n * m;
  int peak = (min_sum + max_sum) / 2;
  double chosen_combinations = 0;

  memo.assign(n+1, vector<double>(max_sum + 1, -1));
  cerr << combinations_range(6, 8, 2) << "\n";

  int range_a = 10000;
  int range_b = 0;
  int i = peak;
  bool up = false;
  for (int j = 0; j < k; ++j) {
    i += j * (up ? 1 : -1);
    up = !up;

    int x = i <= peak ? i : 2 * peak - i;
    range_a = min(x, range_a);
    range_b = max(x, range_b);
  }
  chosen_combinations = combinations_range(range_a, range_b, n);

  double probability = (double)chosen_combinations / (double)total_combinations;
  cout << probability << "\n";
}
