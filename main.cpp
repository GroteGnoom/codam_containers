
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

template <typename T>
void capactiy_print(vector<T> &v) {
	std::cout << "v: " << v << "\n";
	std::cout << "size: " << v.size() << "\n";
	std::cout << "max_size: " << v.max_size() << "\n";
	std::cout << "capacity: " << v.capacity() << "\n";
	std::cout << "empty: " << v.empty() << "\n";
}

int main() {
	std::cout << "\nConstructor 1: default constructor\n";
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

	std::cout << "\nConstructor 2: fill constructor\n";
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
	std::cout << "\nConstructor 3: range constructor\n";
	{
		std::cout << "fill with 10 strings of \"bla\", then take 7: \n";
		vector<std::string> v(10, "bla");
		vector<std::string> v2(v.begin() + 2, v.end() - 1);
		print_vec(v2);
	}
	{
		std::cout << "fill with 10 strings of \"bla\", then take 0: \n";
		vector<std::string> v(10, "bla");
		vector<std::string> v2(v.begin() + 5, v.end() - 5);
		print_vec(v2);
	}
	{
		std::cout << "fill with 10 strings of \"bla\", then take -2: \n";
		vector<std::string> v(10, "bla");
		try {
			vector<std::string> v2(v.begin() + 6, v.end() - 6);
		} catch(std::exception &e) {
			std::cout << "error: " << e.what() << "\n";
		}
	}
	std::cout << "\nConstructor 4: copy constructor\n";
	{
		std::cout << "fill with 10 strings of \"bla\" and take a copy: \n";
		vector<std::string> v(10, "bla");
		vector<std::string> v2(v);
		print_vec(v2);
	}
	{
		std::cout << "make empty vector and take a copy: \n";
		vector<std::string> v(0);
		vector<std::string> v2(v);
		print_vec(v2);
	}
	std::cout << "\nCopy assignment\n";
	{
		std::cout << "fill with 10 strings of \"bla\" and take a copy: \n";
		vector<std::string> v(10, "bla");
		vector<std::string> v2;
		v2 = v;
		print_vec(v2);
	}
	{
		std::cout << "make empty vector and take a copy: \n";
		vector<std::string> v(0);
		vector<std::string> v2;
		v2 = v;
		print_vec(v2);
	}
	std::cout << "\niterators\n";
	{
		std::cout << "fill with 10 numbers: \n";
		vector<int> v(10);
		for (int i = 0; i < 10; i++) {
			v[i] = i;
		}
		std::cout << "begin: " << *v.begin() << "\n";
		std::cout << "end: " << *(v.end() - 1) << "\n";
		//TODO: std::cout << "rbegin: " << *(v.rbegin()) << "\n";
		//TODO: std::cout << "rend: " << *(v.rend()) << "\n";
	}
	std::cout << "\nCapactiy:\n";
	{
		std::cout << "fill with 10 bla strings: \n";
		vector<std::string> v(10, "bla");
		capactiy_print(v);
		std::cout << "resize to 2: \n";
		v.resize(2);
		capactiy_print(v);
		std::cout << "resize to 20: \n";
		v.resize(20);
		capactiy_print(v);
		std::cout << "resize to 0: \n";
		v.resize(0);
		capactiy_print(v);
	}
	std::cout << "\nCapactiy, reserve:\n";
	{
		std::cout << "fill with 10 bla strings: \n";
		vector<std::string> v(10, "bla");
		capactiy_print(v);
		std::cout << "reserve to 2: \n";
		v.reserve(2);
		capactiy_print(v);
		std::cout << "reserve to 20: \n";
		v.reserve(20);
		capactiy_print(v);
		std::cout << "reserve to 0: \n";
		v.reserve(0);
		capactiy_print(v);
	}
	std::cout << "\nElement access";
	{
		std::cout << "fill with 10 bla strings: \n";
		vector<std::string> v(10, "bla");
		const vector<std::string> vc(10, "bla");
		std::cout << "print const vec: \n";
		print_vec(vc);
		std::cout << "set 3: \n";
		v[3] = "bloe";
		print_vec(v);
		std::cout << "set 5 with at: \n";
		v.at(5) = "blie";
		print_vec(v);
		std::cout << "try to set 15 with at: \n";
		try { 
			v.at(15) = "blie";
		} catch (std::out_of_range &e) {
			std::cout << e.what() << "\n";
		}
		print_vec(v);
		std::cout << "front: " << v.front() << "\n";
		std::cout << "const front: " << vc.front() << "\n";
		std::cout << "back: " << v.back() << "\n";
		std::cout << "const back: " << vc.back() << "\n";
	}
	std::cout << "\nModifiers";
	{
		std::cout << "fill with 10 bla strings: \n";
		vector<std::string> v(10, "bla");
		{
			std::cout << "replace 3 string with bloe: \n";
			vector<std::string> v2(3, "bloe");
			v.assign(v2.begin(), v2.end());
			print_vec(v);
		}
		{
			std::cout << "replace 1 string with blie: \n";
			vector<std::string> v2(1, "blie");
			v.assign(v2.begin(), v2.end());
			print_vec(v);
		}
		{
			std::cout << "replace 20 string with blieoe: \n";
			vector<std::string> v2(20, "blieoe");
			v.assign(v2.begin(), v2.end());
			print_vec(v);
			std::cout << "resize to 3, so it's more readable: \n";
			v.resize(3);
		}
		{
			std::cout << "add bleh and blah: \n";
			v.push_back("bleh");
			v.push_back("blah");
			print_vec(v);
		}
		{
			std::cout << "pop back\n";
			v.pop_back();
			print_vec(v);
			std::cout << "pop back\n";
			v.pop_back();
			print_vec(v);
		}
		{
			std::cout << "pop back\n";
			v.pop_back();
			print_vec(v);
			std::cout << "pop back\n";
			v.pop_back();
			print_vec(v);
		}
		{
			std::cout << "insert wioe at index 1\n";
			v.insert(v.begin() + 1, "wioe");
			print_vec(v);
		}
		{
			std::cout << "insert 3 wiii at index 0\n";
			v.insert(v.begin(), 3, "wiii");
			print_vec(v);
		}
		{
			std::cout << "insert 3 waaa at index 0 via iterator\n";
			vector<std::string> v2(10, "waaa");
			v.insert(v.begin(), v2.begin() + 3, v2.end() - 4);
			print_vec(v);
		}
	}
}

