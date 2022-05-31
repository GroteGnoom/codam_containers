#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "vector_iterator.hpp"

namespace ft {


//iterator traits
#define trait(a) typedef typename Iterator::a a
template <class Iterator>
class iterator_traits {
	public:
		trait(difference_type);
		trait(value_type);
		trait(pointer);
		trait(reference);
		trait(iterator_category);
};
#undef trait

template <class T>
class iterator_traits<T*> {
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T*> {
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
};

//reverse_iterator
template<typename Itr>
class reverse_iterator {
    Itr current;
public:
	typedef Itr iterator_type;
	typedef typename iterator_traits<Itr>::iterator_category iterator_category ;
	typedef typename iterator_traits<Itr>::value_type value_type;
	typedef typename iterator_traits<Itr>::difference_type difference_type;
	typedef typename iterator_traits<Itr>::pointer pointer;
	typedef typename iterator_traits<Itr>::reference reference;

	//Constructors
	reverse_iterator() : current(Itr()) {};
	explicit reverse_iterator( iterator_type x ) : current(x) {};
	template< class U >
	reverse_iterator( const reverse_iterator<U>& other ) : current(other.current) {};

	//Copy assignment
	template< class U >
	reverse_iterator& operator=( const reverse_iterator<U>& other ) {
		current = other.base();
	};

	Itr base() { return current; }

	value_type& operator*() const {
		Itr i = current;
		i--;
		return *i;
	}
	value_type* operator->() const { 
		return std::addressof(operator*());
   	}
	value_type& operator[](size_t idx) {
		return *(current - idx);
	}
	const value_type& operator[](size_t idx) const {
		return *(current - idx);
	}
	reverse_iterator &operator++() {
		current -= 1;
		return *this;
	}
	reverse_iterator operator++(int) {
		return reverse_iterator(current--);
	}
	reverse_iterator &operator+=(difference_type a) {
		current -= a;
		return *this;
	}
	reverse_iterator operator+(difference_type a) const {
		return reverse_iterator(current - a);
	}
	reverse_iterator &operator--() {
		current += 1;
		return *this;
	}
	reverse_iterator operator--(int) {
		return reverse_iterator(current++);
	}
	reverse_iterator &operator-=(difference_type a) {
		current += a;
		return *this;
	}
	reverse_iterator operator-(difference_type a) const {
		return reverse_iterator(current + a);
	}
	difference_type operator-(const reverse_iterator &a) const {
		return a.base() - current;
	}
};

template <class T>
struct is_integral{
	static const bool value = false;
};

#define all_int \
	is_int(bool);\
	is_int(char);\
	is_int(signed char);\
	is_int(unsigned char);\
	is_int(wchar_t);\
	is_int(short);\
	is_int(unsigned short);\
	is_int(int);\
	is_int(unsigned int);\
	is_int(long);\
	is_int(unsigned long);\

//the compiler tells me:
//template specialization requires 'template<>'
#define is_int(_type_) template <> struct is_integral<_type_>{ static const bool value = true; }
	all_int
#undef is_int
#define is_int(_type_) template <> struct is_integral<const _type_>{ static const bool value = true; }
	all_int
#undef is_int
#define is_int(_type_) template <> struct is_integral<volatile const _type_>{ static const bool value = true; }
	all_int
#undef is_int
#define is_int(_type_) template <> struct is_integral<volatile _type_>{ static const bool value = true; }
	all_int
#undef is_int

template <typename it1, typename it2>
bool lexicographical_compare(it1 b1, it1 e1, it2 b2, it2 e2) {
	while (true) {
		if (b1 >= e1 && b2 >= e2)
			return false;
		if (b1 >= e1)
			return true;
		if (b2 >= e2)
			return false;
		if (*b1 < *b2)
			return true;
		if (*b1 > *b2)
			return false;
		b1++;
		b2++;
	}
}

template <typename it1, typename it2>
bool equal(it1 b1, it1 e1, it2 b2) {
	while (b1 != e1) {
		if (*b1 != *b2)
			return false;
		b1++;
		b2++;
	}
	return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal (InputIterator1 b1, InputIterator1 e1,
		InputIterator2 b2, BinaryPredicate pred) {
	while (true) {
		if (b1 >= e1)
			return true;
		if (!pred(*b1, *b2))
			return false;
		b1++;
		b2++;
	}
}





// this makes a templated struct. so enable_if<Cond, T>
template<bool Cond, class T = void> struct enable_if {};

//This one only matches if Cond is trye. That means type will get typedefd to T, so you have to put the enable_if::type in place of your normal type
// if the condition is not true the typedef will not happen, and the compler will look for other functions
template<class T> struct enable_if<true, T> { typedef T type; };



}

#endif
