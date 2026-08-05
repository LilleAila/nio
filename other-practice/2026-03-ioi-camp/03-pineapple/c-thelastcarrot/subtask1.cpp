#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  // Subtask 1
  if (n == 2) {
    int total_combinations = m * m;
    int min_sum = n;
    int max_sum = n * m;

    int chosen_combinations = 0;

    int peak = m+1;
    int i = peak; // Most probable outcome
    bool up = false;
    for (int j = 0; j < k; ++j) {
      i += j * (up ? 1 : -1);
      up = !up;
      // cerr << i << "\n";

      int x = i <= peak ? i : 2 * peak - i;
      int c = x - 1;
      chosen_combinations += c;
    }

    double probability = (double)chosen_combinations / (double)total_combinations;
    cout << probability << "\n";

    return 0;
  }
}
