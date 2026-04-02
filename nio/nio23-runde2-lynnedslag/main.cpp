#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> ds(n+1, 0);
  while (k--) {
    int a, b;
    cin >> a >> b;
    ds[a] += 1;
    ds[b + 1] -= 1;
  }

  vector<int> prefix(n+1);
  partial_sum(ds.begin(), ds.end(), prefix.begin());

  int houses = 0;
  for (const auto &x : prefix) {
    if (x % 2 == 0) {
      houses++;
    }
  }

  houses--;
  cout << houses << endl;
}
