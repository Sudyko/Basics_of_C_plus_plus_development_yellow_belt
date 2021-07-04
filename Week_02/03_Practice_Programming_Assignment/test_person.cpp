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

// Test persons that don't have first_name or last_name or both.
void TestUnknowns() {
    Person person;
    person.ChangeFirstName(1990, "Anna");
    person.ChangeFirstName(1992, "Sasha");
    person.ChangeLastName(1994, "Smith");
    AssertEqual(person.GetFullName(1920), "Incognito",
                "Ans: Incognito, where year = 1920.");
    AssertEqual(person.GetFullName(1989), "Incognito",
                "Ans: Incognito, where year = 1989");
    AssertEqual(person.GetFullName(1990), "Anna with unknown last name",
                "Ans: Anna + X, where year = 1990.");
    AssertEqual(person.GetFullName(1993), "Sasha with unknown last name",
                "Ans: Sasha + X, where year = 1993.");
    Person person_with_last_name;
    person_with_last_name.ChangeLastName(1992, "Sergeeva");
    person_with_last_name.ChangeLastName(1995, "Ivanova");
    AssertEqual(person_with_last_name.GetFullName(1993),
                "Sergeeva with unknown first name",
                "Ans: X + Sergeeva, where year = 1993.");
    AssertEqual(person_with_last_name.GetFullName(1996),
                "Ivanova with unknown first name",
                "Ans: X + Ivanova, where year = 1996.");
}

// Test persons that have first_name and last_name.
void TestKnowns() {
    Person person;
    person.ChangeFirstName(1892, "Polina");
    person.ChangeLastName(1892, "Sergeeva");
    person.ChangeFirstName(1900, "Sasha");
    person.ChangeLastName(1902, "Ivanova");
    AssertEqual(person.GetFullName(1892), "Polina Sergeeva",
                "Ans: Polina + Sergeeva, where year = 1892.");
    AssertEqual(person.GetFullName(1901), "Sasha Sergeeva",
                "Ans: Sasha Sergeeva, where year = 1901.");
    AssertEqual(person.GetFullName(1903), "Sasha Ivanova",
                "Ans: Sasha + Ivanova, where year = 1903.");
}

int main() {
    TestRunner runner;
    // добавьте сюда свои тесты
    runner.RunTest(TestUnknowns, "TestUnknowns");
    runner.RunTest(TestKnowns, "TestKnowns");
    return 0;
}