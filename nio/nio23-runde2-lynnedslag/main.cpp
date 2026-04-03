#include <iostream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<bool> ds(n+1, false);
  while (k--) {
    int a, b;
    cin >> a >> b;
    ds[a] = !ds[a];
    ds[b + 1] = !ds[b+1];
  }

  int state = 1;
  int houses = 0;
  for (int i = 0; i <= n; i++) {
    state ^= ds[i];
    if (state) {
      houses++;
    }
  }

  houses--;
  cout << houses << endl;
}
