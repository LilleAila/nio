#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<vector<int>> prefix(n + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= n; i++) {
    string row;
    cin >> row;

    for (int j = 1; j <= n; j++) {
      prefix[i][j] = prefix[i][j - 1] + prefix[i - 1][j] -
                     prefix[i - 1][j - 1] + (row[j - 1] == '*');
    }
  }

  while (q--) {
    int y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    --y1; // Use 0-indexed half-open intervals
    --x1;
    int result =
        prefix[y2][x2] - prefix[y2][x1] - prefix[y1][x2] + prefix[y1][x1];
    cout << result << endl;
  }
}
