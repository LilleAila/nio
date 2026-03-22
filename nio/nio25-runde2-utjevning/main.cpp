// rust seems easier i don't want to learn all this c stuff :sob:
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  int k;
  cin >> n >> k;

  vector<int> h;
  for (int i = 0; i < n; i++) {
    int hi;
    cin >> hi;
    h.push_back(hi);
  }

  for (int x : h)
    cout << x << " ";
  cout << endl;

  return 0;
}
