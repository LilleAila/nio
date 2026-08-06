#include <iostream>
#include <climits>
#include <utility>
#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int xmin, xmax;
  cin >> xmin >> xmax;

  int q;
  cin >> q;

  // Map of serial number to camera range
  unordered_map<ll, tuple<ll, ll, ll>> cameras_by_serial;
  multiset<tuple<ll, ll, ll>> camera_ranges;
  multiset<tuple<ll, ll, ll>> camera_ranges2;

  for (int i = 0; i < q; ++i) {
    char operation;
    cin >> operation;

    if (operation == '+') {
      ll s, a, b;
      cin >> s >> a >> b;
      if (a < xmin) a = xmin;
      if (b > xmax) b = xmax;
      ll end = b >= xmax ? 1 : 0;
      cameras_by_serial.insert({s, {a, b, end}});
      camera_ranges.insert({a, b, end});
      camera_ranges2.insert({end, a, b});
    } else {
      ll s;
      cin >> s;
      auto [serial, range] = *cameras_by_serial.find(s);
      auto [ra, rb, re] = range;
      cameras_by_serial.erase(serial);
      camera_ranges.erase(camera_ranges.find(range));
      camera_ranges2.erase(camera_ranges2.find({re, ra, rb}));
    }

    // cerr << "\n";
    // for (const auto &[a, b] : camera_ranges) cerr << "[" << a << ", " << b << "] ";
    // cerr << "\n";
    // for (const auto &[a, b] : camera_ranges_rev) cerr << "[" << a << ", " << b << "] ";
    // cerr << "\n";

    if (camera_ranges.size() == 0) {
      cout << "-1" << "\n";
      continue;
    }

    // Find the range with a <= xmin and the greatest possible b
    auto l_it = camera_ranges.upper_bound({xmin, LLONG_MAX, 1});
    if (l_it == camera_ranges.begin()) {
      cout << "-1" << "\n";
      continue;
    }

    auto [l1, l2, le] = *prev(l_it);
    if (l1 > xmin) {
      cout << "-1" << "\n";
      continue;
    }
    // cerr << "[" << l1 << ", " << l2 << "]" << "\n";
    if (l2 >= xmax) {
      cout << "1" << "\n";
      continue;
    }

    // Find the range with a <= l2 that reaches end
    auto r_it = camera_ranges2.lower_bound({1, 0, 0});
    if (r_it == camera_ranges2.end()) {
      cout << "-1" << "\n";
      continue;
    }

    auto [re, r1, r2] = *r_it;
    if (!re) {
      cout << "-1" << "\n";
      continue;
    }
    // cerr << "[" << l1 << ", " << l2 << "] + [" << r1 << ", " << r2 << "]" << "\n";
    if (r1 > l2) {
      cout << "-1" << "\n";
      continue;
    }
    if (r2 >= xmax) {
      cout << "2" << "\n";
      continue;
    }

    cout << "-1" << "\n";
  }
}
