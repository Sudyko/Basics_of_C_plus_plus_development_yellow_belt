#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

void PrintPermutations(vector<int>& v) {
    vector<vector<int>> result;
    do {
        result.push_back({begin(v), end(v)});
    } while (next_permutation(begin(v), end(v)));
    reverse(begin(result), end(result));
    for (const auto& item : result) {
        for (int i = 0; i < item.size(); ++i)
            cout << item[i] << " ";
        cout << endl;
    }
}

int main() {
    int count;
    cin >> count;
    vector<int> v(count);
    iota(begin(v), end(v), 1);
    PrintPermutations(v);
    return 0;
}