#include <iostream>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, t;
  cin >> n >> t;

  if (t == 1) {
    ll v = 1000000000;
    cout << "? " << v << endl;

    ll d;
    cin >> d;

    ll x1 = -d + v;
    cout << "! " << x1 << endl;
  }

  else if (t == 2) {
    ll v = 1e9;
    cout << "? " << v << endl;

    ll d1, d2;
    cin >> d1 >> d2;

    ll x1 = -(d1 + d2) + v;
  }
}
