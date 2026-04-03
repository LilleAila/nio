#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  int longest_sequence = 0;
  int sequence = 0;
  char prev = s[0];

  for (const auto c : s) {
    if (c == prev) {
      sequence++;
    } else {
    longest_sequence = max(sequence, longest_sequence);
      sequence = 1;
    }
    prev = c;
  }
  longest_sequence = max(sequence, longest_sequence);

  cout << longest_sequence << endl;
}
