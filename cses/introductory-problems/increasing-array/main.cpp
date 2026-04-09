#include <iostream>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  ll moves = 0;

  n--;
  ll prev;
  cin >> prev;
  while (n--) {
    ll x;
    cin >> x;

    if (prev > x) {
      moves += prev - x;
    } else {
      prev = x;
    }
  }

  cout << moves << endl;
}
