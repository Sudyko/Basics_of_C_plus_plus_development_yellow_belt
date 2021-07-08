#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    const int distance = std::distance(range_begin, range_end);
    if (distance < 2) return;
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    auto middle = begin(elements) + distance / 2;
    MergeSort(begin(elements), middle);
    MergeSort(middle, end(elements));
    merge(begin(elements), middle, middle, end(elements), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}