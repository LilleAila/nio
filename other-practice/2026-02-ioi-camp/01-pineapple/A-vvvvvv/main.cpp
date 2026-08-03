#include <iostream>
#include <stack>
#include <array>
#include <tuple>
#include <utility>
#include <queue>
#include <vector>
#include <set>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int w, h, n;
  cin >> w >> h >> n;

  vector<vector<bool>> wall_below(w, vector<bool>(h+1, false));
  vector<vector<bool>> wall_left(w+1, vector<bool>(h, false));

  for (int i = 0; i < n; ++i) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    if (y1 == y2) {
      if (x2 < x1) swap(x2, x1);
      for (int j = x1; j < x2; ++j) {
        wall_below[j][y1] = true;
      }
    } else {
      if (y2 < y1) swap(y2, y1);
      for (int j = y1; j < y2; ++j) {
        wall_left[x1][j] = true;
      }
    }
  }

  // for (auto row : wall_below) {
  //   for (auto cell : row) {
  //     cerr << cell;
  //   }
  //   cerr << "\n";
  // }

  // cerr << wall_below[0][0] << endl;
  // cerr << wall_below[2][0] << endl;
  // cerr << wall_below[7][9] << endl;
  // cerr << wall_left[0][0] << endl;
  // cerr << wall_left[1][1] << endl;

  vector<set<int>> floor(w);
  vector<set<int>> ceiling(w);

  for (int x = 0; x < w; ++x) {
    for (int y = 0; y < h; ++y) {
      if (wall_below[x][y]) floor[x].insert(y);
      if (wall_below[x][y+1]) ceiling[x].insert(y);
    }
  }

  // cerr << "Floor:" << endl;
  // for (int i = 0; i < w; ++i) {
  //   cerr << "x=" << i << ":";
  //   for (const auto x : floor[i]) {
  //     cerr << " " << x;
  //   }
  //   cerr << endl;
  // }

  // {x, y, down}
  queue<tuple<int, int, bool>> q;
  q.push({0, 0, true});
  // q.push({1, 0, true});
  // q.push({1, 4});
  // q.push({1, 8});
  // q.push({1, 5});
  // vector<vector<bool>> visited(w, vector<bool>(h, false));

  // visited[x][y][down ? 1 : 0] = {x_from, y_from, input_char}
  // tuple<int, int, char> unvisited[2] = {{-1, -1, 0}, {-1, -1, 0}};
  vector<vector<vector<tuple<int, int, bool, char>>>> visited(w, vector<vector<tuple<int, int, bool, char>>>(h, vector<tuple<int, int, bool, char>>(2, {-1, -1, false, 0})));

  visited[0][0][1] = {0, 0, true, 0};

  while (!q.empty()) {
    auto [x, y, down] = q.front();
    q.pop();

    // cerr << x << " " << y << " " << down << endl;
    // if (visited[x][y]) continue;
    // visited[x][y] = true;

    if (x == w - 1 && y == h - 1) break;

    // Standing on floor (gravity down)
    if (down) {
      // Go up
      auto above = ceiling[x].lower_bound(y);
      if (above != ceiling[x].end()) {
        if (get<0>(visited[x][*above][0]) == -1) {
          visited[x][*above][0] = {x, y, down, 'G'};
          q.push({x, *above, false});
          // cerr << "G " << x << " " << y << " to " << x << " " << *above << endl;
        }
      }

      // Go left
      if (x > 0 && !wall_left[x][y]) {
        auto &ls = floor[x-1];
        auto left_above = ls.upper_bound(y);
        if (left_above != ls.begin()) {
          auto not_above = prev(left_above);
          if (get<0>(visited[x-1][*not_above][1]) == -1) {
            visited[x-1][*not_above][1] = {x, y, down, 'V'};
            q.push({x-1, *not_above, true});
            // cerr << "V " << x << " " << y << " to " << x-1 << " " << *not_above << endl;
          }
        }
      }

      // Go right
      if (x < w - 1 && !wall_left[x+1][y]) {
        auto &rs = floor[x+1];
        auto right_above = rs.upper_bound(y);
        if (right_above != rs.begin()) {
          auto not_above = prev(right_above);
          if (get<0>(visited[x+1][*not_above][1]) == -1) {
            visited[x+1][*not_above][1] = {x, y, down, 'H'};
            q.push({x+1, *not_above, true});
            // cerr << "H " << x << " " << y << " to " << x+1 << " " << *not_above << endl;
          }
        }
      }
    }

    // Standing on ceiling (gravity up)
    else {
      // Go down
      auto above = floor[x].upper_bound(y);
      if (above != floor[x].begin()) {
        auto below = prev(above);
        if (get<0>(visited[x][*below][1]) == -1) {
          visited[x][*below][1] = {x, y, down, 'G'};
          q.push({x, *below, true});
          // cerr << "G " << x << " " << y << " to " << x << " " << *below << endl;
        }
      }

      // Go left
      if (x > 0 && !wall_left[x][y]) {
        auto &ls = ceiling[x-1];
        auto left_above = ls.lower_bound(y);
        if (left_above != ls.end()) {
          if (get<0>(visited[x-1][*left_above][0]) == -1) {
            visited[x-1][*left_above][0] = {x, y, down, 'V'};
            q.push({x-1, *left_above, false});
            // cerr << "V " << x << " " << y << " to " << x-1 << " " << *left_above << endl;
          }
        }
      }

      // Go right
      if (x < w - 1 && !wall_left[x+1][y]) {
        auto &rs = ceiling[x+1];
        auto right_above = rs.lower_bound(y);
        if (right_above != rs.end()) {
          if (get<0>(visited[x+1][*right_above][0]) == -1) {
            visited[x+1][*right_above][0] = {x, y, down, 'H'};
            q.push({x+1, *right_above, false});
            // cerr << "H " << x << " " << y << " to " << x+1 << " " << *right_above << endl;
          }
        }
      }
    }

    // cerr << endl;

    // if (x > 0 && !wall_left[x][y]) {
    //   auto &ls = valid_locations[x-1];
    //   auto it = ls.upper_bound(y);
    //
    //   if (it != ls.end()) {
    //     cout << "Valid location above: " << *it << endl;
    //   }
    //
    //   if (it != ls.begin()) {
    //     cout << "Valid location below: " << *prev(it) << endl;
    //   }
    // }
  }

  tuple<int, int, bool, char> next;

  if (get<0>(visited[w-1][h-1][1]) != -1) {
    next = visited[w-1][h-1][1];
  } else if (get<0>(visited[w-1][h-1][0]) != -1) {
    next = visited[w-1][h-1][0];
  } else {
    cout << "Inte" << "\n";
    return 0;
  }

  stack<char> result;
  while (true) {
    auto [x, y, d, c] = next;
    // cout << x << " " << y << " " << d << " " << c << endl;
    // cout << c;
    result.push(c);
    next = visited[x][y][d];
    if (x == 0 && y == 0) break;
  }
  while (!result.empty()) {
    char c = result.top();
    result.pop();
    cout << c;
  }
  cout << "\n";
}
