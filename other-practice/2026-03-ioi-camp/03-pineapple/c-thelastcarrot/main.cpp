#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <algorithm>
using ll = long long;
using namespace std;

int n, m, k;

vector<vector<double>> memo;

// O(n^2) - Fast enough for subtasks 1 and 2, but way too slow for adouble others
// With memoization it is also good enough for subtasks 3 and 4,
// but slightly too slow for the final one
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

  int i = peak;
  bool up = false;
  for (int j = 0; j < k; ++j) {
    i += j * (up ? 1 : -1);
    up = !up;

    int x = i <= peak ? i : 2 * peak - i;
    chosen_combinations += combinations(x, n);
  }

  double probability = (double)chosen_combinations / (double)total_combinations;
  cout << probability << "\n";
}
