#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cerr.tie(nullptr);

  array<int, 4> ss;
  cin >> ss[0] >> ss[1] >> ss[2] >> ss[3];
  int total_students = ss[0] + ss[1] + ss[2] + ss[3];
  int total_strength = (ss[0] + ss[1] * 2 + ss[2] * 3 + ss[3] * 4) ;

  int target_strength = total_strength / 2;
  int strength = 0;
  array<int, 4> team = {0, 0, 0, 0};

  for (int s = 4; s > 0; --s) {
    int i = s - 1;
    for (int j = 0; j < ss[i]; ++j) {
      if (strength + s <= target_strength) {
        strength += s;
        ++team[i];
      }
    }
  }

  cout << team[0] << " " << team[1] << " " << team[2] << " " << team[3] << "\n";
}
