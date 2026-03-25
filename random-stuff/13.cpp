#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string line;
  getline(cin, line);
  stringstream ss(line);
  vector<int> xs;
  int x;
  while (ss >> x) {
    xs.push_back(x);
  }

  cout << "[ ";
  for (auto &x : xs)
    cout << x << " ";
  cout << "]" << endl;

  int n;
  cin >> n;
  vector<int> ys;
  while (n--) {
    int y;
    cin >> y;
    ys.push_back(y);
  }

  cout << "[ ";
  for (auto &y : ys)
    cout << y << " ";
  cout << "]" << endl;
}
