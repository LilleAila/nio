#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> as(n);
  vector<int> bs(m);

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    as[i] = a;
  }

  for (int i = 0; i < m; i++) {
    int b;
    cin >> b;
    bs[i] = b;
  }

  sort(as.begin(), as.end());
  sort(bs.begin(), bs.end());

  int apartments = 0;
  for (int i = 0, j = 0; i < n && j < m;) {
    int a = as[i];
    int b = bs[j];

    if (a + k < b) {
      i++;
      continue;
    }
    if (a - k > b) {
      j++;
      continue;
    }

    apartments++;
    i++;
    j++;
  }

  cout << apartments << endl;
}
