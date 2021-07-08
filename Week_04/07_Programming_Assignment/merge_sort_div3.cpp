#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    const int distance = std::distance(range_begin, range_end);
    if (distance < 2) return;
    vector<typename RandomIt::value_type> elements(range_begin, range_end), temp;
    auto middle1 = begin(elements) + distance / 3;
    auto middle2 = begin(elements) + 2 * distance / 3;
    MergeSort(begin(elements), middle1);
    MergeSort(middle1, middle2);
    MergeSort(middle2, end(elements));
    merge(begin(elements), middle1, middle1, middle2,
          back_inserter(temp));
    merge(begin(temp), end(temp), middle2, end(elements), range_begin);
}

int main() {
    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}