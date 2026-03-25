#include <iostream>
using namespace std;

int main() {
  int size = 1001;
  int layers = size / 2 + 1;

  int x = 1;
  int n = 1;

  for (int i = 1; i < layers; i++) {
    for (int j = 0; j < 4; j++) {
      n += 2 * i;
      x += n;
    }
  }

  cout << x << endl;
}
