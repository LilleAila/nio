#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> xs;

  while (n--) {
    int x;
    cin >> x;
    xs.push_back(x);
  }

  sort(xs.begin(), xs.end());
  auto it = unique(xs.begin(), xs.end());
  xs.erase(it, xs.end());

  cout << xs.size() << endl;
}
