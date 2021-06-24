#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <class T>
T Sqr(T x);

template <class T>
vector<T> Sqr(const vector<T>& v);

template <class K, class V>
pair<K, V> Sqr(const pair<K, V>& p);

template <class K, class V>
map<K, V> Sqr(const map<K, V>& m);

template <class T>
T Sqr(T x) {
	return x * x;
}

template <class T>
vector<T> Sqr(const vector<T>& v) {
	vector<T> result;
	for (const T& i : v)
		result.push_back(Sqr(i));
	return result;
}

template <class K, class V>
pair<K, V> Sqr(const pair<K, V>& p) {
	return { Sqr(p.first), Sqr(p.second) };
}

template <class K, class V>
map<K, V> Sqr(const map<K, V>& m) {
	map<K, V> result;
	for (const auto& i : m)
		result[i.first] = Sqr(i.second);
	return result;
}

int main() {
	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};

	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}
	return 0;
}