#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string INF = {'Z' + 1};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n;
  cin >> n;

  vector<string> grid(n);

  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
  }

  string result = "";
  result += grid[0][0];

  vector<pair<int, int>> q;
  q.push_back({0, 0});
  vector<vector<bool>> visited(n, vector<bool>(n, false));

  for (int d = 0; d < 2 * n - 2; ++d) {
    char min_char = 'Z' + 1;
    vector<pair<int, int>> next;

    for (const auto &[y, x] : q) {
      if (x + 1 < n) {
        if (grid[y][x + 1] < min_char) {
          min_char = grid[y][x + 1];
        }
      }

      if (y + 1 < n) {
        if (grid[y + 1][x] < min_char) {
          min_char = grid[y + 1][x];
        }
      }
    }

    result += min_char;

    vector<pair<int, int>> next_q;
    for (const auto &[y, x] : q) {
      if (x + 1 < n && grid[y][x + 1] == min_char && !visited[y][x + 1]) {
        visited[y][x + 1] = true;
        next_q.push_back({y, x + 1});
      }

      if (y + 1 < n && grid[y + 1][x] == min_char && !visited[y + 1][x]) {
        visited[y + 1][x] = true;
        next_q.push_back({y + 1, x});
      }
    }
    q = next_q;
  }

  cout << result << endl;
}
