#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  unordered_map<int, int> klosser;

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    int h;
    int b;
    cin >> h >> b;

    klosser[b] = max(klosser[b], h);
  }

  long long sum = 0;
  for (auto &x : klosser)
    sum += x.second;
  cout << sum << endl;

  return 0;
}
