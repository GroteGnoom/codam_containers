
#ifdef STD
#	include <vector>
	using namespace std;
#	include <iterator>
#	include <typeinfo>
#	include <map>
#else
#	include "vector.hpp"
#	include "map.hpp"
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

#define check_compares(op) do { \
	vector<std::string> v1(5, "bla"); \
	vector<std::string> v2(4, "bla"); \
	std::cout << "one is shorter: " << (v1 op v2) << "\n"; \
	v2.push_back("ble"); \
	std::cout << "last string is not equal: " << (v1 op v2) << "\n"; \
	v2[4] = "bla"; \
	std::cout << "equal: " << (v1 op v2) << "\n"; \
} while (0) \


static void con_def_ass() {
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
}

static void iter() {
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
	{
		std::cout << "\nconst version:\n";
		std::cout << "fill with 10 numbers: \n";
		const vector<int> v(10, 5);
		std::cout << "begin: " << *v.begin() << "\n";
		std::cout << "end: " << *(v.end() - 1) << "\n";
		//TODO: std::cout << "rbegin: " << *(v.rbegin()) << "\n";
		//TODO: std::cout << "rend: " << *(v.rend()) << "\n";
	}
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		vector<int>::const_iterator it = v.begin();
		(void) it;
	}
}

static void capacity() {
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
}

static void elem_acc() {
	std::cout << "\nElement access";
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

static void modifiers() {
	std::cout << "\nModifiers";
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
	{
		vector<int> v2(4);
		v2[0] = 0;
		v2[1] = 1;
		v2[2] = 2;
		v2[3] = 3;
		std::cout << "erase elem 0\n";
		v2.erase(v2.begin());
		print_vec(v2);
	}
	{
		vector<int> v2(4);
		v2[0] = 0;
		v2[1] = 1;
		v2[2] = 2;
		v2[3] = 3;
		std::cout << "erase elem 1 and 2\n";
		std::cout << *v2.erase(v2.begin() + 1, v2.end() - 1) << "\n";
		print_vec(v2);
	}
	{
		vector<int> v1(4);
		v1[0] = 0;
		v1[1] = 1;
		v1[2] = 2;
		v1[3] = 3;
		vector<int> v2(4);
		v2[0] = 4;
		v2[1] = 5;
		v2[2] = 6;
		v2[3] = 7;
		int *i = &v1[0];
		std::cout << "before swap: " << *i << "\n";
		print_vec(v1);
		print_vec(v2);
		v1.swap(v2);
		std::cout << "after swap: " << *i << "\n";
		print_vec(v1);
		print_vec(v2);
	}	
	{
		std::cout << "clear: \n";
		vector<std::string> v1(5, "bla");
		v1.clear();
		print_vec(v1);
	}
}

static void alloc() {
	std::cout << "\nModifiers";
	std::cout << "allocator: \n";
	vector<std::string> v1(5, "bla");
	std::string *p;
	p = v1.get_allocator().allocate(3);
	for (int i = 0; i < 3; i++) {
		v1.get_allocator().construct(p + i, "jaja ");
	}
	for (int i = 0; i < 3; i++) {
		std::cout << p[i];
	}
	std::cout << "\n";
	for (int i = 0; i < 3; i++) {
		v1.get_allocator().destroy(p + i);
	}
	v1.get_allocator().deallocate(p, 3);
}

static void non_member() {
	std::cout << "\nNon-member function overloads\n";
	std::cout << "Relational operators:\n";
	{
		std::cout << "equal: \n";
		check_compares(==);
	}
	{
		std::cout << "not equal: \n";
		check_compares(!=);
	}
	{
		std::cout << "less than: \n";
		check_compares(<);
	}
	{
		std::cout << "less than or equal: \n";
		check_compares(<=);
	}
	{
		std::cout << "greater than \n";
		check_compares(>);
	}
	{
		std::cout << "greater than or equal: \n";
		check_compares(>=);
	}
	std::cout << "swap:\n";
	{
		vector<std::string> v1(5, "bla");
		vector<std::string> v2(3, "bleh");
		vector<std::string> v3;

		swap(v1, v2);
		swap(v2, v3);

		std::cout << "3 blehs:\n";
		print_vec(v1);
		std::cout << "empty:\n";
		print_vec(v2);
		std::cout << "5 blas:\n";
		print_vec(v3);
	}
}

static void it_traits() {
	std::cout << "iterator traits: \n";
	//vector<int>::iterator a(NULL);
	vector<int>::value_type b;
	//(void) a;
	(void) b;

	//vector<int> c;
	//c.value_type d; // simply not allowed
	//(void) c;
	//(void) d;
	//typedef iterator_traits< vector<int *> > traits;
	//if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
	//	std::cout << "int * is a random-access iterator";
	typedef iterator_traits< vector<int>::iterator > traits;
	if (typeid(traits::iterator_category)==typeid(random_access_iterator_tag)) {
		std::cout << "vector<int>::iterator is a random-access iterator\n";
	}
}

template <class T>
typename enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}


template <class T>
typename enable_if<!std::is_integral<T>::value,bool>::type
  is_odd (T i) {std::cout << i << " is not integral\n"; return false;}

void check_enable_if() {
	std::cout << "enable if: \n";
	double a = 2;
	std::cout << "double should give a warning and false: \n";
	std::cout << is_odd(a) << "\n";
	int b = 2;
	std::cout << "int should give false: \n";
	std::cout << is_odd(b) << "\n";
}

void typedefs() {
#define check_type(a) do {(void)sizeof(vector<int>::a);} while (0)
	check_type(value_type);
	check_type(allocator_type);
	check_type(reference);
	check_type(const_reference);
	check_type(pointer);
	check_type(const_pointer);
	check_type(iterator);
	check_type(const_iterator);
	//TODO check_type(reverse_iterator);
	//TODO check_type(const_reverse_iterator);
	check_type(difference_type);
	check_type(size_type);
#undef check_type
}

void test_vector() {
	typedefs();
	con_def_ass();
	iter();
	capacity();
	elem_acc();
	modifiers();
	alloc();
	non_member();
	it_traits();
	check_enable_if();
}

void test_map() {
#define check_type(a) do {(void)sizeof(map<std::string, int>::a);} while (0)
	check_type(key_type);
	check_type(mapped_type);
	check_type(value_type);
	check_type(key_compare);
#undef check_type
}

int main() {
	test_vector();
	test_map();
}

