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

void TestRationalClass() {
    AssertEqual(Rational().Numerator(), 0,
                "Canonical form of default constructed is 0/1.");
    AssertEqual(Rational().Denominator(), 1,
                "Canonical form of default constructed is 0/1.");
    AssertEqual(Rational(4, 6).Numerator(), 2,
                "Canonical form for 4/6 is 2/3.");
    AssertEqual(Rational(4, 6).Denominator(), 3,
                "Canonical form for 4/6 is 2/3.");
    AssertEqual(Rational(-6, 7).Numerator(), -6,
                "Canonical form of -6/7 is -6/7.");
    AssertEqual(Rational(-6, 7).Denominator(), 7,
                "Canonical form of -6/7 is -6/7.");
    AssertEqual(Rational(3, -5).Numerator(), -3,
                "Canonical form of 3/-5 is -3/5.");
    AssertEqual(Rational(3, -5).Denominator(), 5,
                "Canonical form of 3/-5 is -3/5.");
    AssertEqual(Rational(0, 232).Numerator(), 0,
                "Canonical form of 0/232 is 0/1.");
    AssertEqual(Rational(0, 232).Denominator(), 1,
                "Canonical form of 0/232 is 0/1.");
    AssertEqual(Rational(2147483647, 2147483647).Numerator(), 1,
                "Canonical form of 2147483647/2147483647 is 1/1.");
    AssertEqual(Rational(2147483647, 2147483647).Denominator(), 1,
                "Canonical form of 2147483647/2147483647 is 1/1.");
    AssertEqual(Rational(-5, -10).Numerator(), 1,
                "Canonical form of -5/-10 is 1/2.");
    AssertEqual(Rational(-5, -10).Denominator(), 2,
                "Canonical form of -5/-10 is 1/2.");
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestRationalClass, "TestRationalClass");
    return 0;
}