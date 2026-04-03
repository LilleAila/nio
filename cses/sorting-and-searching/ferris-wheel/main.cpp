#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, x;
  cin >> n >> x;

  vector<int> ps(n);
  for (int i = 0; i < n; i++) {
    int p;
    cin >> p;
    ps[i] = p;
  }

  sort(ps.begin(), ps.end());

  int g = 0;
  for (int i = 0, j = n-1; i <= j;) {
    int a = ps[i];
    int b = ps[j];

    if (a + b <= x) {
      g++;
      i++;
      j--;
    } else {
      g++;
      j--;
    }
  }

  cout << g << endl;
}
