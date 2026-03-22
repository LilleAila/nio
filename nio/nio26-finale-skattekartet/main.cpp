#include <bits/stdc++.h>
using namespace std;

#define dbg(x) cerr << __FILE__ << ":" << __LINE__ << " " << #x << " = " << (x) << endl;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string mode;
  cin >> mode;

  if (mode == "kartlegg") {
    int n, x, y;
    cin >> n >> x >> y;
    // In reality we just want log2(n) but i hard coded it for simplicity
    int bits = n == 16 ? 4 : n == 4 ? 2 : 1;

    // 0-indexed to make my life easier
    y -= 1;
    x -= 1;

    int dy = n - y - 1;
    int dx = n - x - 1;
    for (int i = 0; i < bits; i++) {
      if (y & (1 << i)) {
        cout << "marker " << i + 2 << " 1" << endl;
      }

      if (dy & (1 << i)) {
        cout << "marker " << n - i - 1 << " " << n << endl;
      }

      if (x & (1 << i)) {
        cout << "marker 1 " << n - i - 1 << endl;
      }

      if (dx & (1 << i)) {
        cout << "marker " << n << " " << i + 2 << endl;
      }
    }

    cout << "avslutt" << endl;
  } else if (mode == "let") {
    int n;
    cin >> n;
    int bits = n == 16 ? 4 : n == 4 ? 2 : 1;

    // change back to 1-indexed
    int x = 1;
    int y = 1;
    for (int i = 0; i < bits; i++) {
      string c;

      cout << "sjekk " << i + 2 << " 1" << endl;
      cin >> c;
      if (c == "mynt") {
        y += 1 << i;
      }

      cout << "sjekk 1 " << n - i - 1 << endl;
      cin >> c;
      if (c == "mynt") {
        x += 1 << i;
      }
    }

    cout << "skatt " << x << " " << y << endl;
  }
}
