#include <iostream>
#include <vector>

int main() {
    int n, count = 0;
    int64_t sum = 0;
    std::cin >> n;
    std::vector<int> t(n);
    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i];
        sum += t[i];
    }
    sum /= n;
    for (int i = 0; i < n; ++i) {
        if (t[i] > sum) {
            result.push_back(i);
            ++count;
        }
    }
    std::cout << count << std::endl;
    for (auto day : result)
        std::cout << day << " ";
    return 0;
}