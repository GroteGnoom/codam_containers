
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

template <typename T>
void print_vec(vector<T> v) {
	std::cout << "v: " << v << "\n";
}

int main() {
	std::cout << "Constructor 1: default constructor\n";
	{
		std::cout << "int: \n";
		vector<int> v;
		print_vec(v);
	}
	{
		std::cout << "string: \n";
		vector<std::string> v;
		print_vec(v);
	}

	std::cout << "Constructor 2: fill constructor\n";
	{
		std::cout << "fill with 10 strings: \n";
		vector<std::string> v(10);
		print_vec(v);
	}
	{
		std::cout << "fill with 10 ints: \n";
		vector<int> v(10);
		print_vec(v);
	}
	{
		std::cout << "fill with 10 strings of \"bla\": \n";
		vector<std::string> v(10, "bla");
		print_vec(v);
	}
	{
		std::cout << "fill with 0 strings of \"bla\": \n";
		vector<std::string> v(0, "bla");
		print_vec(v);
	}
	{
		std::cout << "fill with 10 strings of \"bla\", then take 7: \n";
		vector<std::string> v(10, "bla");
		vector<std::string> v2(v.begin() + 2, v.end() - 1);
		print_vec(v2);
	}
}

