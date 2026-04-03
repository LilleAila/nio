#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  unordered_set<int> xs;

  for (int i = 0; i < n - 1; i++) {
    int x;
    cin >> x;
    xs.insert(x);
  }

  for (int i = 1; i <= n; i++) {
    if (xs.count(i) == 0) {
      cout << i << endl;
      break;
    }
  }
}
