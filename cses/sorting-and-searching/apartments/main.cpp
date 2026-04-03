#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  map<int, int> as;
  while (n--) {
    int a;
    cin >> a;
    as[a]++;
  }

  vector<int> bs;
  while (m--) {
    int b;
    cin >> b;
    bs.push_back(b);
  }

  sort(bs.begin(), bs.end());

  int apartments = 0;
  for (const auto b : bs) {
    auto it = as.lower_bound(b - k);
 
    for (; it != as.end() && it->first <=b+k; it++) {
      apartments++;
      it->second--;
      if (it->second == 0) as.erase(it);
      break;
    }
  }

  cout << apartments << endl;
}
