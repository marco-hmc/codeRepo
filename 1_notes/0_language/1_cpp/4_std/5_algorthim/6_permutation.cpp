#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> v{istream_iterator<string>{cin}, {}};
    sort(begin(v), end(v));
    do {
        copy(begin(v), end(v), ostream_iterator<string>{cout, ", "});
        cout << '\n';
    } while (next_permutation(begin(v), end(v)));
    return 0;
}