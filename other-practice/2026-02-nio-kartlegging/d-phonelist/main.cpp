#include <iostream>
#include <memory>
#include <array>
#include <vector>
using namespace std;

struct Node {
  char value;
  array<unique_ptr<Node>, 10> children;
  bool end = false;

  Node(char value) : value(value) {}

  bool insert(string s) {
    if (end) {
      return false;
    }

    if (s.empty()) {
      end = true;

      for (int i = 0; i < 10; ++i) {
        if (children[i] != nullptr) {
          return false;
        }
      }

      return true;
    }

    char head = s.front() - '0';
    string xs = s.substr(1);

    if (children[head] == nullptr) {
      children[head] = make_unique<Node>(head);
    }

    return children[head]->insert(xs);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Node root(' ');
  // cerr << root.insert("911") << endl;
  // cerr << root.insert("97625999") << endl;
  // cerr << root.insert("91125426") << endl;
  // return 0;

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    Node root(' ');
    bool valid = true;

    while (n--) {
      string s;
      cin >> s;

      if (valid && !root.insert(s)) {
        valid = false;
      }
    }

    cout << (valid ? "YES" : "NO") << "\n";
  }
}
