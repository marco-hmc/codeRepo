#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace std {
ostream &operator<<(ostream &os, const pair<int, string> &p) {
  return os << "(" << p.first << ", " << p.second << ")";
}
} // namespace std

int main() {
  vector<pair<int, string>> v{
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  map<int, string> m;

  copy_n(begin(v), 3, inserter(m, begin(m)));

  auto shell_it(ostream_iterator<pair<int, string>>{cout, ", "});

  copy(begin(m), end(m), shell_it);
  cout << '\n';

  m.clear();

  move(begin(v), end(v), inserter(m, begin(m)));

  copy(begin(m), end(m), shell_it);
  cout << '\n';

  copy(begin(v), end(v), shell_it);
  cout << '\n';
}