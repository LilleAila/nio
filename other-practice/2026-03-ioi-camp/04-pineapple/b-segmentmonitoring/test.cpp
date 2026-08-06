#include <iostream>
#include <climits>
#include <set>
#include <utility>
using namespace std;
using ll = long long;

int main() {
  multiset<pair<ll, ll>> test;

  {
    auto it = test.lower_bound({2, 0});
    if (it != test.end()) {
      auto [a, b] = *it;
      cout << "[" << a << ", " << b << "]" << endl;
    }
  }

  test.insert({1, 0});
  {
    auto it = prev(test.lower_bound({2, 0}));
    if (it != test.end()) {
      auto [a, b] = *it;
      cout << "[" << a << ", " << b << "]" << endl;
    }
  }

  test.erase({1, 0});
  test.insert({2, 0});
  {
    auto it = prev(test.upper_bound({1, LLONG_MAX}));
    if (it != test.begin()) {
      auto [a, b] = *prev(it);
      cout << "[" << a << ", " << b << "]" << endl;
    }
  }

}
