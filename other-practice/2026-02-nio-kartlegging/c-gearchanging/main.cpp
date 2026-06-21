#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int n, m, p;
  cin >> n >> m >> p;

  vector<double> cs(n);
  for (int i = 0; i < n; ++i) cin >> cs[i];
  vector<double> ds(m);
  for (int i = 0; i < m; ++i) cin >> ds[i];

  priority_queue<double> ratios;
  for (double c : cs) {
    for (double d : ds) {
      double ratio = c / d;
      ratios.push(ratio);
    }
  }

  double prev = ratios.top();
  ratios.pop();

  while (!ratios.empty()) {
    double next = ratios.top();
    ratios.pop();

    double diff = prev / next - 1;
    if (diff * 100 > p) {
      cout << "Time to change gears!" << "\n";
      return 0;
    }

    prev = next;
  }

  cout << "Ride on!" << "\n";
}
