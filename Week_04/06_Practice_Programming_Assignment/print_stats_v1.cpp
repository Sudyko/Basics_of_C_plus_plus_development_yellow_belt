void PrintStats(vector<Person> persons) {
    auto pivot = partition(begin(persons), end(persons),
                           [](const Person& person) {
                               return person.gender == Gender::FEMALE;
                           });
    vector<Person> females = {begin(persons), pivot};
    vector<Person> males = {pivot, end(persons)};
    cout << "Median age = "
         << ComputeMedianAge(begin(persons), end(persons)) << endl
         << "Median age for females = "
         << ComputeMedianAge(begin(females), end(females)) << endl
         << "Median age for males = "
         << ComputeMedianAge(begin(males), end(males)) << endl;
    pivot = partition(begin(females), end(females),
                      [](const Person& person) { return person.is_employed; });
    cout << "Median age for employed females = "
         << ComputeMedianAge(begin(females), pivot) << endl
         << "Median age for unemployed females = "
         << ComputeMedianAge(pivot, end(females)) << endl;
    pivot = partition(begin(males), end(males),
                      [](const Person& person) { return person.is_employed; });
    cout << "Median age for employed males = "
         << ComputeMedianAge(begin(males), pivot) << endl
         << "Median age for unemployed males = "
         << ComputeMedianAge(pivot, end(males)) << endl;
}