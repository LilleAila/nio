#include <iostream>
#include <iomanip>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  double i;
  cin >> i;

  for (int j = 0; j < 30; ++j) {
    double x;
    cin >> x;

    i = max(i * (100 + x) / 100.0, i + x);
  }

  cout << fixed << setprecision(6) << i << "\n";
}
