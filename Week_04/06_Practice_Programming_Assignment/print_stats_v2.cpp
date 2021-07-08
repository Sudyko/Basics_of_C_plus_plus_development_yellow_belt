void PrintStats(vector<Person> persons) {
    auto female_end = partition(begin(persons), end(persons),
                                [](const Person& person) {
                                    return person.gender == Gender::FEMALE;
                                });
    auto employed_females_end = partition(begin(persons), female_end,
                                          [](const Person& person) {
                                              return person.is_employed;
                                          });
    auto employed_males_end = partition(female_end, end(persons),
                                        [](const Person& person) {
                                            return person.is_employed;
                                        });
    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons)) << endl
         << "Median age for females = "
         << ComputeMedianAge(begin(persons), female_end) << endl
         << "Median age for males = "
         << ComputeMedianAge(female_end, end(persons)) << endl
         << "Median age for employed females = "
         << ComputeMedianAge(begin(persons), employed_females_end) << endl
         << "Median age for unemployed females = "
         << ComputeMedianAge(employed_females_end, female_end) << endl
         << "Median age for employed males = "
         << ComputeMedianAge(female_end, employed_males_end) << endl
         << "Median age for unemployed males = "
         << ComputeMedianAge(employed_males_end, end(persons)) << endl;
}