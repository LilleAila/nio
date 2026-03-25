#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

int digitsSum(int n) {
  int sum = 0;
  n = abs(n);
  while (n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

vector<int> properDivisors(int n) {
  vector<int> divisors;
  if (n <= 1)
    return divisors;
  divisors.push_back(1);
  for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
      divisors.push_back(i);
      if (i != n / i) {
        divisors.push_back(n / i);
      }
    }
  }
  sort(divisors.begin(), divisors.end());
  return divisors;
}

int main() {
  const int max = 28123;

  unordered_set<int> abundant;

  for (int i = 0; i <= max; i++) {
    vector<int> divisors = properDivisors(i);
    int sum = accumulate(divisors.begin(), divisors.end(), 0);
    if (sum > i) {
      abundant.insert(i);
    }
  }

  cout << "{ ";
  for (const auto &x : abundant)
    cout << x << " ";
  cout << "}" << endl;

  vector<int> xs;

  for (int i = 0; i <= max; i++) {
    for (const auto &n : abundant) {
      if (abundant.count(i - n) > 0) {
        goto next;
      }
    }
    xs.push_back(i);
  next:;
  }

  cout << "[ ";
  for (const auto &x : xs)
    cout << x << " ";
  cout << "]" << endl;

  int sum = accumulate(xs.begin(), xs.end(), 0);
  cout << sum << endl;
}
