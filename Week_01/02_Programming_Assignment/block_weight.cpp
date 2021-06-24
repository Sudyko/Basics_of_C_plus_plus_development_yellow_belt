#include <iostream>

int main() {
    int n, r;
    uint64_t sum = 0;
    std::cin >> n >> r;
    for (int i = 0; i < n; ++i) {
        uint64_t volume = 1;
        for (char j = 0; j < 3; ++j) {
            uint16_t size;
            std::cin >> size;
            volume *= size;
        }
        sum += volume * r;
    }
    std::cout << sum << std::endl;
    return 0;
}