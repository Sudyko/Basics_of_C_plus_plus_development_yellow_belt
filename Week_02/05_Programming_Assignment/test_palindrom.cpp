#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator<<(ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
   public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

   private:
    int fail_count = 0;
};

bool IsPalindrom(const string& str) {
    // Вы можете вставлять сюда различные реализации функции,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный
}

void TestPalindromFunc() {
    Assert(IsPalindrom(""), "Empty string is a palindrome.");
    Assert(IsPalindrom("s"),
           "A string that consists of 1 letter is a palindrome.");
    Assert(IsPalindrom("madam"), "A string `madam` is a palindrome.");
    Assert(IsPalindrom("maddam"), "A string `maddam` is a palindrome.");
    Assert(IsPalindrom("m a d a m"), "A string `m a d a m` is a palindrome.");
    Assert(IsPalindrom(" madam "), "A string ` madam ` is a palindrome.");
    Assert(!IsPalindrom("XmadamY"),
           "A string `XmadamY` is not a palindrome.");
    Assert(!IsPalindrom("abbaX"), "A string `abbaX` is not a palindrome.");
    Assert(!IsPalindrom("Xabba"), "A string `Xabba` is not a palindrome.");
    Assert(!IsPalindrom("abXYba"), "A string `abXYba` is not a palindrome.");
    Assert(!IsPalindrom("  madam"),
           "A string `  madam` is not a palindrome.");
    Assert(!IsPalindrom("madam  "),
           "A string `madam  ` is not a palindrome.");
    Assert(!IsPalindrom("was it a car or a cat i saw"),
           "A string `was it a car or a cat i saw` is not a palindrome.");
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestPalindromFunc, "TestPalindromFunc");
    return 0;
}