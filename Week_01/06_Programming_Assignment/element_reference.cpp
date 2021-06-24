#include <iostream>
#include <map>

using namespace std;

template <class K, class V>
V& GetRefStrict(map<K, V>& m, K k) {
	if (m.count(k) == 0)
		throw runtime_error("no such key");
	return m[k];
}

int main() {
	map<int, string> m = { {0, "value"} };
	string& item = GetRefStrict(m, 0);
	item = "newvalue";
	cout << m[0] << endl; // выведет newvalue
	return 0;
}