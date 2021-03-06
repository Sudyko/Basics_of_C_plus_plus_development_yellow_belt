#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s) {
    os << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << "{";
    bool first = true;
    for (const auto &kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string &hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
   public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string &test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception &e) {
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

int GetDistinctRealRootCount(double a, double b, double c) {
    // ???? ???????????? ?????????????????? ???????? ?????????????????? ???????????????????? ??????????????,
    // ?????????? ??????????????????, ?????? ???????? ?????????? ???????????????????? ???????????????????? ??????
    // ?? ?????????? ????????????????????????
}

void TestRootCount() {
    AssertEqual(GetDistinctRealRootCount(5, -4, -1), 2,
                "Ans: 2, where 5x^2 - 4 - 1 = 0.");  // D = 1
    AssertEqual(GetDistinctRealRootCount(-1, 3, 10), 2,
                "Ans: 2, where -x^2 + 3x + 10.");  // D = 16
}

void TestOneRoot() {  // D = 0
    AssertEqual(GetDistinctRealRootCount(1, -6, 9), 1,
                "Ans: 1, where x^2 -6x + 9 = 0.");
    AssertEqual(GetDistinctRealRootCount(1, 4, 4), 1,
                "Ans: 1, where x^2 + 4x + 4 = 0.");
}

void TestNoRoots() {
    AssertEqual(GetDistinctRealRootCount(-6, 0, -7), 0,
                "Ans: 0, where -6x^2 - 7 = 0.");
    AssertEqual(GetDistinctRealRootCount(5, -1, 2), 0,
                "Ans: 0, where 5x^2 - x + 2 = 0.");
}

void TestConstant() {
    AssertEqual(GetDistinctRealRootCount(0, 0, 100), 0,
                "Ans: 0, where a = 0, b = 0 and c = 100.");
    AssertEqual(GetDistinctRealRootCount(0, 0, -100), 0,
                "Ans: 0, where a = 0, b = 0 and c = -100.");
}

int main() {
    TestRunner runner;
    // ???????????????? ???????? ???????? ??????????
    runner.RunTest(TestConstant, "TestConstant");
    runner.RunTest(TestNoRoots, "TestNoRoots");
    runner.RunTest(TestOneRoot, "TestOneRoot");
    runner.RunTest(TestRootCount, "TestRootCount");
    return 0;
}