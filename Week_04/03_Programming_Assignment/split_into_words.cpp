#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> result;
    auto it = begin(s), iter = begin(s);
    while (true) {
        it = find(iter, end(s), ' ');
        result.push_back(string(iter, it));
        if (it == end(s))
            break;
        iter = it + 1;
    }
    return result;
}

int main() {
    string s = "C Cpp Java Python";
    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;
    return 0;
}