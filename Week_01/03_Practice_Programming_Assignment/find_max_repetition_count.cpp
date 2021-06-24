#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

bool operator<(const Region& lhs, const Region& rhs) {
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
        tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const std::vector<Region>& regions) {
    int count = 0;
    std::map<Region, int> m;
    for (const auto& r : regions) {
        count = std::max(count, ++m[r]);
    }
    return count;
}