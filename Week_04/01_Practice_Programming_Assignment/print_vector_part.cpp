#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename It>
void PrintReverse(It begin_range, It end_range) {
    auto it = end_range;
    while (it != begin_range) {
        --it;
        cout << *it << " ";
    }
}

void PrintVectorPart(const vector<int>& numbers) {
    auto border = find_if(begin(numbers), end(numbers), [](const int& num) {
        return num < 0; });
    PrintReverse(begin(numbers), border);
}

int main() {
    PrintVectorPart({6, 1, 8, -5, 4});
    cout << endl;
    PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
    cout << endl;
    PrintVectorPart({6, 1, 8, 5, 4});
    cout << endl;
    return 0;
}