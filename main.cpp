
#ifdef STD
#include <vector>
using namespace std;
#else
#include "vector.hpp"
using namespace ft;
#endif

#include <iostream>

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
	for (unsigned i = 0; i < v.size(); i++) { 
		if (i)
			out << " ";
		out << v[i];
	}
	return out;
}

int main() {
	vector<int> v;

	vector<int> v2(10);
	vector<int> v3(10, 3);
	vector<int> v4(v3.begin() + 1, v3.end() - 1);

	std::cout << "v:" << v << "\n";
	std::cout << "v2:" << v2 << "\n";
	std::cout << "v3:" << v3 << "\n";
	std::cout << "v4:" << v4 << "\n";
}

