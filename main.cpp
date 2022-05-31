
#ifdef STD
#	include <vector>
	using namespace std;
#	include <iterator>
#	include <typeinfo>
#	include <map>
template <typename T>
void print_avl(void *a , int spaces ) {
	(void) a;
	(void) spaces;
}
#else
#	include "vector.hpp"
#	include "map.hpp"
	using namespace ft;
template <typename T, class Alloc>
void print_avl(ft::Avlnode<T, Alloc> *a , int spaces ) {
	if (!a) return;
	print_avl(a->_right, spaces + 5 );
	for (int i = 1; i <= spaces; ++i ) {
		std::cout << " ";
	}
	std::cout << a->_elem << "," << a->get_height() << "," << a->get_balance() << "\n";
	print_avl( a->_left, spaces + 5 );
}

#endif

#include <iostream>
#include "printing.hpp"

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
	vector<std::string> v1(4, "bla"); \
	vector<std::string> v2(5, "bla"); \
	std::cout << "first is shorter: " << (v1 op v2) << "\n"; \
	v1.push_back("ble"); \
	std::cout << "last string is not equal: " << (v1 op v2) << "\n"; \
	v1[4] = "bla"; \
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
		std::cout << "rbegin: " << *(v.rbegin()) << "\n";
		std::cout << "rend: " << *(v.rend() - 1) << "\n";
	}
	{
		std::cout << "\nconst version:\n";
		std::cout << "fill with 10 numbers: \n";
		const vector<int> v(10, 5);
		std::cout << "begin: " << *v.begin() << "\n";
		std::cout << "end: " << *(v.end() - 1) << "\n";
		std::cout << "rbegin: " << *(v.rbegin()) << "\n";
		std::cout << "rend: " << *(v.rend() - 1) << "\n";
	}
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		vector<int>::const_iterator it = v.begin();
		vector<int>::const_iterator it2 = v.end();
		it++;
		std::cout << *(++it) << "\n";
		std::cout << *(--it) << "\n";
		std::cout << *(it++) << "\n";
		std::cout << *(it--) << "\n";
		std::cout << *it++ << "\n";
		std::cout << *it-- << "\n";

		std::cout << *(it+1) << "\n";
		std::cout << *(1+it) << "\n";
		std::cout << *(it-1) << "\n";
		std::cout << it2-it << "\n";

		std::cout << (it < it2) << "\n";
		std::cout << (it > it2) << "\n";
		std::cout << (it <= it2) << "\n";
		std::cout << (it >= it2) << "\n";
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

void rev_it() {
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
	vector<int>::reverse_iterator ri1 = v1.rbegin();
	//vector<int>::reverse_iterator ri2 = v2.rbegin();
	std::cout << (ri1 < v1.rbegin()) << "\n";
	std::cout << (ri1 <= v1.rbegin()) << "\n";
	std::cout << (ri1 > v1.rbegin()) << "\n";
	std::cout << (ri1 >= v1.rbegin()) << "\n";
	std::cout << (ri1 == v1.rbegin()) << "\n";
	std::cout << (ri1 != v1.rbegin()) << "\n";
	std::cout << *(ri1 + 1) << "\n";
	std::cout << *(v1.rend() - 1) << "\n";
	std::cout << *(1 + ri1) << "\n";
	std::cout << (ri1 - v1.rbegin()) << "\n";
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
	check_type(reverse_iterator);
	check_type(const_reverse_iterator);
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
	rev_it();
}

template <class Key, class T>
Key it_to_key(typename map<Key, T>::iterator it, map<Key, T> &m) {
	if (it == m.end()) {
		std::cout << "iterator at end!\n";
		return Key();
	}
	return it->first;
}


void print_elems(map<std::string, int> &m) {
	for (map<std::string, int>::iterator first = m.begin(); first != m.end(); first++) {
		std::cout << first->first << " " << first->second << "\n";
	}
}

static void test_map_constructors() {
	std::cout << "Constructors:\n";
	std::cout << "default constructor:\n";
	map<std::string, int> m;
	m["a"] = 100;
	m["b"] = 11;
	std::cout << "copy constructor:\n";
	map<std::string, int> m2 = m;
	std::cout << "after copy constructor:\n";
	m2["d"] = 4;
	m2["c"] = 5;
	print_elems(m);
	print_elems(m2);
	map<std::string, int> m3;
	m3 = m;
	m3["e"] = 6;
	m3["f"] = 7;
	print_elems(m);
	print_elems(m3);
}

static void test_map_iterators() {
	map<std::string, int> m;
	m["a"] = 100;
	m["b"] = 11;
	m["la"] = 101;
	m["blba"] = 5;
	map<std::string, int>::iterator i1 = m.begin();
	map<std::string, int>::iterator i2 = m.end();
	map<std::string, int>::reverse_iterator i3 = m.rbegin();
	map<std::string, int>::reverse_iterator i4 = m.rend();
	map<std::string, int>::iterator i6(i2);
	map<std::string, int>::reverse_iterator i7(i3);
	
	std::cout << *i1 << "\n";
	std::cout << *(--i2) << "\n";
	std::cout << i3->first << "\n";

	map<std::string, int>::reverse_iterator i5;
	i5 = i4;
	std::cout << (i3 == i5) << "\n";
	std::cout << (i3 != i5) << "\n";
	std::cout << *(++i3) << "\n";
	std::cout << *(i3--) << "\n";
	std::cout << *(i3++) << "\n";
	std::cout << *(--i3) << "\n";
	std::cout << *(--i6) << "\n";
	std::cout << *(i7) << "\n";

}

static void test_map_capacity() {
	map<std::string, int> m;

	std::cout << "Capacity\n";
	std::cout << "Is empty map empty? " << m.empty() << "\n";
	std::cout << "What is its size?" << m.size() << "\n";
	pair<map<std::string, int>::iterator, bool> a = m.insert(pair<std::string, int>("hoi", 5));
	std::cout << "Is non-empty map empty? " << m.empty() << "\n";
	std::cout << "What is its size?" << m.size() << "\n";
	std::cout << "What the dereferenced iterator key? " << (*(a.first)).first << "\n";
	std::cout << "What the dereferenced iterator key via ->? " << a.first->first << "\n";
	std::cout << "What the dereferenced iterator value? " << (*(a.first)).second << "\n";
	std::cout << "What the dereferenced iterator value via ->? " << a.first->second << "\n";
	a = m.insert(pair<std::string, int>("hoi", 10));
	std::cout << "Try to add the same key, should do nothing, so same key has same value: " << a.first->second << "\n";
	//std::cout << "What is the max size?" << m.max_size() << "\n"; They don't have to be the same. Maybe nodes will be bigger with more state to make things quicker
	a = m.insert(pair<std::string, int>("banaan", 20));
	std::cout << "Try to add different key: " << a.first->second << "\n";
}

static void test_map_element_access() {
	map<std::string, int> m;
	//Element access
	m["aa"] = 10;
	std::cout << "add aa = 10, aa is " << m["aa"] << "\n";
	m["a"] = 20;
	std::cout << "add a = 20, a is " << m["a"] << "\n";
	std::cout << "aa a is " << m["aa"] << "\n";
	std::cout << "bb is " << m["bb"] << "\n";
	std::cout << "bb is " << m["bb"] << "\n";
	std::cout << "bb is " << m["bb"] << "\n";

	std::cout << "What is its size? " << m.size() << "\n";
	m.erase("a");
	std::cout << "after erasing a is " << m["a"] << "\n";
	std::cout << "What is its size? " << m.size() << "\n";
}

static void test_map_modifiers() {
	map<std::string, int> m;
	m.insert(pair<std::string, int>("hoi", 10));
	//modifiers
	//
	//insert is already tested
	map<std::string, int>::iterator it;
	it = m.find("hoi");
	std::cout << "is find equal to end? " << (it == m.end()) << "\n";
	std::cout << "erase element\n";
	m.erase("hoi");
	std::cout << "What is its size?" << m.size() << "\n";
	it = m.find("hoi");
	std::cout << "is find equal to end? " << (it == m.end()) << "\n";


	map<std::string, int> m2;

	m2["asdfa"] = 12;
	std::cout << "What is the size of a new tree" << m.size() << "\n";
	m.swap(m2);
	std::cout << "What is the size old tree after swap" << m.size() << "\n";
	std::cout << "What is the size the new tree after swap" << m2.size() << "\n";
	m.clear();
	std::cout << "What is the size old tree after clear" << m.size() << "\n";
}

static void test_map_observers() {
	map<std::string, int> m;

	map<std::string, int>::key_compare kc = m.key_comp();
	std::cout << "compare a and b:" << kc("a", "b") << "\n";

	map<std::string, int>::value_compare vc = m.value_comp();

	map<std::string, int>::value_type v1;
	map<std::string, int>::value_type v2;
	std::cout << "compare with value type:" << vc(v1, v2) << "\n";
}

static void test_map_operations() {
	map<std::string, int> m;
	map<std::string, int> m2;

	m2["aa"] = 12;
	m2["ablaa"] = 12;
	std::cout << "count aa: " << m2.count("aa") << "\n";
	std::cout << "count cc: " << m2.count("cc") << "\n";

	std::cout << "lower bound a: " << it_to_key(m2.lower_bound("a"), m2) << "\n";
	std::cout << "lower bound b: " << it_to_key(m2.lower_bound("b"), m2) << "\n";
	std::cout << "lower bound c: " << it_to_key(m2.lower_bound("c"), m2) << "\n";

	std::cout << "upper bound a: " << it_to_key(m2.upper_bound("a"), m2) << "\n";
	std::cout << "upper bound b: " << it_to_key(m2.upper_bound("b"), m2) << "\n";
	std::cout << "upper bound c: " << it_to_key(m2.upper_bound("c"), m2) << "\n";

	std::cout << "range a: " << it_to_key(m2.equal_range("a").first, m2) << " " << it_to_key(m2.equal_range("a").second, m2) << "\n";
	std::cout << "range b: " << it_to_key(m2.equal_range("b").first, m2) << " " << it_to_key(m2.equal_range("b").second, m2) << "\n";
	std::cout << "range c: " << it_to_key(m2.equal_range("c").first, m2) << " " << it_to_key(m2.equal_range("c").second, m2) << "\n";
}

static void test_map_allocator() {
	std::cout << "allocator: \n";
	map<std::string, int> m;
	pair<const std::string, int> *p;
	p = m.get_allocator().allocate(3);
	for (int i = 0; i < 3; i++) {
		m.get_allocator().construct(p + i, pair<std::string, int>("jaja ", 5));
	}
	for (int i = 0; i < 3; i++) {
		std::cout << p[i];
	}
	std::cout << "\n";
	for (int i = 0; i < 3; i++) {
		m.get_allocator().destroy(p + i);
	}
	m.get_allocator().deallocate(p, 3);
}

static void test_reverse_iterator() {
	vector<int> v;
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);

	reverse_iterator<vector<int>::iterator> ri1;
	vector<int>::iterator i1 = v.begin();
	i1++;
	i1++;

	reverse_iterator<vector<int>::iterator> ri2(i1);
	reverse_iterator<vector<int>::iterator> ri3 = ri2;

	vector<int>::iterator b = ri2.base();
	std::cout << *b << "\n";


	std::cout << *ri2 << "\n";
	std::cout << *(++ri2++) << "\n";
	std::cout << *(--ri2--) << "\n";
	std::cout << *(ri2 + 1) << "\n";
	std::cout << *(ri2 - 1) << "\n";
	ri2 += 1;
	ri2 -= 1;
	std::cout << *ri2 << "\n";
	std::cout << (ri2 < ri3) << "\n";
	std::cout << (ri2 <= ri3) << "\n";
	std::cout << (ri2 > ri3) << "\n";
	std::cout << (ri2 >= ri3) << "\n";
	std::cout << (ri2 == ri3) << "\n";
	std::cout << (ri2 != ri3) << "\n";

	ri1 = ri2;
	ri1--;
	std::cout << (ri2 < ri1) << "\n";
	std::cout << (ri2 <= ri1) << "\n";
	std::cout << (ri2 > ri1) << "\n";
	std::cout << (ri2 >= ri1) << "\n";
	std::cout << (ri2 == ri1) << "\n";
	std::cout << (ri2 != ri1) << "\n";
	std::cout << (ri2 - ri1) << "\n";
	std::cout << *(1 + ri1) << "\n";
}

void test_map() {
#define check_type(a) do {(void)sizeof(map<std::string, int>::a);} while (0)
	check_type(key_type);
	check_type(mapped_type);
	check_type(value_type);
	check_type(key_compare);
	check_type(value_compare);
	check_type(allocator_type);
	check_type(reference);
	check_type(const_reference);
	check_type(pointer);
	check_type(const_pointer);
	check_type(iterator);
	check_type(const_iterator);
	check_type(reverse_iterator);
	check_type(const_reverse_iterator);
	check_type(difference_type);
	check_type(size_type);
#undef check_type
	test_map_constructors();
	test_map_iterators();
	test_map_capacity();
	test_map_element_access();
	test_map_modifiers();
	test_map_observers();
	test_map_operations();
	test_map_allocator();
}

void test_pair() {
	pair<std::string, int> p1;
	pair<std::string, int> p2 ("bla", 5);
	pair<std::string, int> p3(p2);
	pair<std::string, int> p4("bloe", 6);
	p1 = p2;

	std::cout << (p2 == p4) << "\n";
	std::cout << (p2 != p4) << "\n";
	std::cout << (p2 < p4) << "\n";
	std::cout << (p2 <= p4) << "\n";
	std::cout << (p2 > p4) << "\n";
	std::cout << (p2 >= p4) << "\n";
	p1 = make_pair("asf", 7);
}


int main() {
	test_pair();
	test_vector();
	test_map();
	test_reverse_iterator();
}
