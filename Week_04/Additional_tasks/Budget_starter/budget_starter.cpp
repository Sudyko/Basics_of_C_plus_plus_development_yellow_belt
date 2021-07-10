#include <time.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

string ReadToken(string& str, const char& delimeter) {
    auto pivot = find(begin(str), end(str), delimeter);
    string result = string(begin(str), pivot);
    str = string(next(pivot), end(str));
    return result;
}

class Date {
   public:
    static Date FromString(string str) {
        const int year = stoi(ReadToken(str, '-'));
        const int month = stoi(ReadToken(str, '-'));
        const int day = stoi(str);
        return {year, month, day};
    }

    time_t MakeTimeStamp() const {
        tm time;
        time.tm_sec = 0;
        time.tm_min = 0;
        time.tm_hour = 0;
        time.tm_mday = day_;
        time.tm_mon = month_ - 1;
        time.tm_year = year_ - 1900;
        time.tm_isdst = 0;
        return mktime(&time);
    }

   private:
    int year_;
    int month_;
    int day_;

    Date(int year, int month, int day) {
        year_ = year;
        month_ = month;
        day_ = day;
    }
};

int ComputeDaysDiff(const Date& date_to, const Date& date_from) {
    const time_t timestamp_to = date_to.MakeTimeStamp();
    const time_t timestamp_from = date_from.MakeTimeStamp();
    constexpr int SECONDS_IN_DAY = 60 * 60 * 24;
    return (timestamp_to - timestamp_from) / SECONDS_IN_DAY;
}

static const Date START_DATE = Date::FromString("2000-01-01");
static const Date END_DATE = Date::FromString("2100-01-01");
static const int DAY_COUNT = ComputeDaysDiff(END_DATE, START_DATE);

int main() {
    vector<double> money(DAY_COUNT, .0);
    size_t q;
    cin >> q;
    for (size_t i = 0; i < q; ++i) {
        string cmd, date_from, date_to;
        cin >> cmd >> date_from >> date_to;
        Date from = Date::FromString(date_from);
        Date to = Date::FromString(date_to);
        auto start_idx = ComputeDaysDiff(from, START_DATE);
        auto end_idx = ComputeDaysDiff(to, START_DATE);
        if (cmd == "Earn") {
            double value;
            cin >> value;
            value /= end_idx - start_idx + 1;
            for (int j = start_idx; j <= end_idx; ++j)
                money[j] += value;
        } else {
            cout << accumulate(begin(money) + start_idx,
                               begin(money) + end_idx + 1, 0.)
                 << endl;
        }
    }

    return 0;
}