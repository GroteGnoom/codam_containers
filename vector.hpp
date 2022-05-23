#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef> //NULL
#include <memory> /* allocator */
#include <iostream>
#include "iterator.hpp"

namespace ft {

struct random_access_iterator_tag {};



template <typename T, typename Distance>
class ra_iterator : public general_iterator<random_access_iterator_tag, T, Distance> {
	typedef general_iterator<random_access_iterator_tag, T, Distance> base;
	private:
	public:
		typename base::pointer _pointer;
		typedef ra_iterator<const T, Distance> const_iter;
		ra_iterator(const typename base::pointer &p) : _pointer(p) {} //TODO remove?
		ra_iterator(const ra_iterator &it) : _pointer(it._pointer) {}
		ra_iterator &operator=(const ra_iterator &it) {
			_pointer = it._pointer;
			return *this;
		}
		ra_iterator() : _pointer(NULL) {}
		ra_iterator operator+(Distance a) const {
			ra_iterator i = *this;
			i._pointer += a;
			return i;
		}
		ra_iterator &operator+=(Distance a) {
			_pointer += a;
			return *this;
		}
		ra_iterator &operator-=(Distance a) {
			_pointer -= a;
			return *this;
		}
		ra_iterator &operator++() {
			_pointer += 1;
			return *this;
		}
		ra_iterator &operator++(int) {
			ra_iterator &tmp = *this;
			_pointer += 1;
			return tmp;
		}
		ra_iterator &operator--() {
			_pointer -= 1;
			return *this;
		}
		ra_iterator &operator--(int) {
			ra_iterator &tmp = *this;
			_pointer -= 1;
			return tmp;
		}
		ra_iterator operator-(Distance a) const {
			ra_iterator i = *this;
			i._pointer -= a;
			return i;
		}
		T& operator[](size_t idx) {
			return *(_pointer + idx);
		}
		const T& operator[](size_t idx) const {
			return *(_pointer + idx);
		}
		typename base::difference_type operator-(const ra_iterator &rai) const {
			return _pointer - rai._pointer;
		}
		typename base::difference_type operator-(ra_iterator<const T, Distance> &rai) const {
			return _pointer - rai._pointer;
		}
		/*
		operator ra_iterator< const T, Distance> () const {
			return (ra_iterator< const T, Distance>(_pointer));
		}
		*/
		operator const_iter () const
		{
			return (const_iter(_pointer));
		}

#define op(a) bool operator a (const const_iter &rai) const { return _pointer a rai._pointer; }
		op(<)
		op(>)
		op(<=)
		op(>=)
		op(==)
		op(!=)
#undef op
		T* operator->() const { return _pointer; }
		T& operator*() const { return *_pointer; }
};

template <typename T, typename Distance>
class rev_ra_iterator : public general_iterator<random_access_iterator_tag, T, Distance> {
	typedef general_iterator<random_access_iterator_tag, T, Distance> base;
	private:
	public:
		typename base::pointer _pointer;
		rev_ra_iterator(typename base::pointer p) : _pointer(p) {} //TODO remove?
		rev_ra_iterator() : _pointer(NULL) {}
		rev_ra_iterator(const rev_ra_iterator &it) : _pointer(it._pointer) {}
		rev_ra_iterator &operator=(const rev_ra_iterator &it) {
			_pointer = it._pointer;
			return *this;
		}
		operator rev_ra_iterator< const T, Distance> () const {
			return (rev_ra_iterator< const T, Distance>(_pointer));
		}
		rev_ra_iterator operator+(Distance a) const {
			rev_ra_iterator i = *this;
			i._pointer -= a;
			return i;
		}
		rev_ra_iterator &operator+=(Distance a) {
			_pointer -= a;
			return *this;
		}
		rev_ra_iterator &operator-=(Distance a) {
			_pointer += a;
			return *this;
		}
		rev_ra_iterator &operator++() {
			_pointer -= 1;
			return *this;
		}
		rev_ra_iterator &operator++(int) {
			rev_ra_iterator &tmp = *this;
			_pointer -= 1;
			return tmp;
		}
		rev_ra_iterator &operator--() {
			_pointer += 1;
			return *this;
		}
		rev_ra_iterator &operator--(int) {
			rev_ra_iterator &tmp = *this;
			_pointer += 1;
			return tmp;
		}
		rev_ra_iterator operator-(Distance a) const {
			rev_ra_iterator i = *this;
			i._pointer += a;
			return i;
		}
		T& operator[](size_t idx) {
			return *(_pointer - idx);
		}
		const T& operator[](size_t idx) const {
			return *(_pointer - idx);
		}
		typename base::difference_type operator-(rev_ra_iterator<const T, Distance> &rai) const {
			return rai._pointer - _pointer;
		}
		T* operator->() const { return _pointer; }
		T& operator*() const { return *_pointer; }
};

template <typename T, typename Distance>
ra_iterator<T, Distance> operator+(ptrdiff_t a, const ra_iterator<T, Distance> &b) {
	return b + a;
}

template <typename T, typename Distance>
rev_ra_iterator<T, Distance> operator+(ptrdiff_t a, const rev_ra_iterator<T, Distance> &b) {
	return b + a;
}


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

template <typename T, typename Alloc = std::allocator<T> >
class vector {
	public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef size_t size_type;
	typedef ra_iterator<T, size_type> iterator;
	typedef ra_iterator<const T, size_type> const_iterator;
	//typedef const iterator const_iterator; //TODO wrong, right? should be const T, not const iterator
	typedef rev_ra_iterator<T, size_type> reverse_iterator;
	typedef rev_ra_iterator<const T, size_type> const_reverse_iterator;
	typedef ptrdiff_t difference_type; //TODO is it always ptrdiff?
	//typedef reverse_ra_iterator<T, size_type> reverse_iterator;
	private:
	allocator_type _alloc;
	size_type _size;
	size_type _cap;
	T *_data;
	public:
	//typedef reverse_ra_iterator<T, size_type> reverse_iterator;
	//constructor, destructor, assignment
	// empty container constructor
	explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _cap(0), _data(NULL) {};

	//fill constructor
	explicit vector (size_type n, const T& val = T(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _cap(n), _data(_alloc.allocate(n)) {
		for (size_type i = 0; i < _size; i++) {
			_data[i] = val;
		}
	}

	//range constructor
	vector (ra_iterator<T, size_type> first, ra_iterator<T, size_type> last, const allocator_type& alloc = allocator_type()) :
		_alloc(alloc), _size(last - first), _cap(_size) {
			if (first < last) {
				_data = _alloc.allocate(_cap);
			}
			else if (first == last) {
				_data = NULL;
				return;
			} else {
				_size = 0;
				_cap = 0;
				_data = NULL;
				throw std::length_error("vector");
			}
			for (size_type i = 0; first < last; first++) {
				_data[i++] = *first;
			}
		}

	//copy constructor
	vector (const vector& v) : _alloc(v._alloc), _size(v._size), _cap(v._cap), _data(_alloc.allocate(_cap)) {
		for (size_type i = 0; i < _size; i++) {
			_data[i] = v._data[i];
		}
	}

	~vector() {
		resize(0);
		if (_size) {
			clear();
		}
		if (_data)
		{
			_alloc.deallocate(_data, _cap);
			_data = NULL;
			_cap = 0;
		}
	}

	//copy assignment
	vector &operator=(const vector& v) {
		this->~vector<T>(); //TODO slower than necessary, could use old allocation if new size <= old cap
		_alloc = v._alloc;
		_size = v._size;
		_cap = v._cap;
		if (_cap)
			_data = _alloc.allocate(_cap);
		for (size_type i = 0; i < _size; i++) {
			_data[i] = v._data[i];
		}
		return (*this);
	}

	//iterators

	iterator begin() {
		return iterator(_data);
	}
	const_iterator begin() const {
		return iterator(_data);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(_data + _size - 1);
	}
	const_reverse_iterator rbegin() const {
		return reverse_iterator(_data + _size - 1);
	}
	iterator end() {
		return begin() + _size;
	}
	const_iterator end() const {
		return begin() + _size;
	}
	reverse_iterator rend() {
		return _data -1;
	}
	const_reverse_iterator rend() const {
		return _data -1;;
	}

	//TODO: rbegin, rend
	//Capacity

	size_type size() const {return _size;}
	size_type max_size() const {return std::numeric_limits<size_type>::max() / sizeof(T);}

	void resize(size_type n, value_type val = value_type()) {
		if (n < _size) {
			for (size_type i = n; i < _size; i++) {
				_data[i].~T();
			}
			_size = n;
		} else {
			reserve(n);
			for (size_type i = _size; i < n; i++) {
				_data[i] = val;
			}
			_size = n;
			_cap = n;
		}
	}
	size_type capacity() const {return _cap;}
	bool empty() const { return !_size; }
	void reserve(size_type n) {
		if (!_data) {
			_cap = n;
			_data = _alloc.allocate(_cap);
			return;
		}
		if (n > max_size())
			throw std::length_error("vector");
		if (n > _cap) {
			T* new_data = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++) {
				new_data[i] = _data[i];
				_data[i].~T();
			}
			_alloc.deallocate(_data, _cap);
			_data = new_data;
			_cap = n;
		}
	}

	//Element access:
	T& operator[](size_type idx) { return _data[idx]; }

	const T& operator[](size_type idx) const { return _data[idx]; }

	//https://stackoverflow.com/questions/123758/how-do-i-remove-code-duplication-between-similar-const-and-non-const-member-func
	T& at(const size_type n) {
		return const_cast<T &>(const_cast <const vector<T> &> (*this).at(n));
	}
	const T& at (size_type n) const {
		if (n < 0 || n >= _size)
			throw std::out_of_range("vector");
		return _data[n];
	}
	T& front() {
		//https://www.cplusplus.com/reference/vector/vector/front/
		//Calling this function on an empty container causes undefined behavior.
		return _data[0];
	}
	const T&front() const {
		//https://www.cplusplus.com/reference/vector/vector/front/
		//Calling this function on an empty container causes undefined behavior.
		return _data[0];
	}
	T& back() {
		//https://www.cplusplus.com/reference/vector/vector/back/
		//Calling this function on an empty container causes undefined behavior.
		return _data[_size - 1];
	}
	const T&back() const {
		//https://www.cplusplus.com/reference/vector/vector/back/
		//Calling this function on an empty container causes undefined behavior.
		return _data[_size - 1];
	}

	//Modifiers
	//

	template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			if (!(first < last) && !(first == last)) {
				throw std::length_error("vector");
			}
			resize(last - first);
			for (size_type i = 0; first < last; first++) {
				_data[i++] = *first;
			}
		}
	void assign (size_type n, const value_type& val) {
		resize(n);
		for (size_type i = 0; i < n; i++) {
			_data[i] = val;
		}
	}


	void push_back (const value_type& val) {
		if (_cap == _size) {
			if (_cap * 2 + 1 <= max_size())
				reserve(_cap * 2 + 1);
			else
				reserve(_cap + 1);
		}
		_data[_size] = val;
		_size++;
	}
	//If the container is not empty, the function never throws exceptions (no-throw guarantee).
	//Otherwise, it causes undefined behavior.
	void pop_back() {
		resize(_size - 1);
	}

	iterator insert (iterator position, const value_type& val) {
		iterator position_copy = position;
		size_t idx = position - begin();
		resize(_size + 1);
		T s = val;
		for (; begin() + idx < end(); idx++) {
			T n = *(begin() + idx);
			*(begin() + idx) = s;
			s = n;
		}
		return position_copy;
	}

	void insert (iterator position, size_type n, const value_type& val) {
		size_type start = position - begin();
		resize(_size + n);
		for (size_type i = _size - 1; i >= start + n; i--) {
			_data[i] = _data[i - n];
		}
		for (size_type i = 0; i < n ; i++) {
			(*this)[start + i] = val;
		}
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last) {
		size_type start = position - begin();
		size_type n = last - first;
		resize(_size + n);
		for (size_type i = _size - 1; i >= start + n; i--) {
			_data[i] = _data[i - n];
		}
		for (size_type i = 0; i < n ; i++) {
			(*this)[start + i] = *(first + i);
		}
	}

	iterator erase (iterator position) {
		iterator position_copy = position;
		_size --;
		for (;position < end(); position++) {
			*position = *(position + 1);
		}
		return position_copy;
	}

	iterator erase (iterator first, iterator last) {
		for (;last < end(); last++) {
			*first = *last;
			first++;
		}
		_size -= (last-first);
		return last - 1;
	}
	void swap (vector& x) {
		std::swap(_alloc, x._alloc);
		std::swap(_size, x._size);
		std::swap(_cap, x._cap);
		std::swap(_data, x._data);
	}
	void clear() {
		for (size_type i = 0; i < _size; i++) {
			_data[i].~T();
		}
		_size = 0;
	}
	allocator_type get_allocator() const {
		return _alloc;
	}
};

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

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return lhs < rhs || lhs == rhs;
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return !(lhs <= rhs);
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
	return lhs > rhs || lhs == rhs;
}

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
	x.swap(y);
}

// this makes a templated struct. so enable_if<Cond, T>
template<bool Cond, class T = void> struct enable_if {};

//This one only matches if Cond is trye. That means type will get typedefd to T, so you have to put the enable_if::type in place of your normal type
// if the condition is not true the typedef will not happen, and the compler will look for other functions
template<class T> struct enable_if<true, T> { typedef T type; };

} //namespace ft
#endif
