#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef> //NULL
#include <memory> /* allocator */
#include <iostream>
#include "iterator.hpp"
#include "rest.hpp"

namespace ft {

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
	//typedef ra_iterator<T, size_type> iterator;
	//typedef ra_iterator<const T, size_type> const_iterator;
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef rev_ra_iterator<T> reverse_iterator;
	typedef rev_ra_iterator<const T> const_reverse_iterator;
	typedef ptrdiff_t difference_type;
	private:
	allocator_type _alloc;
	size_type _size;
	size_type _cap;
	iterator _data;
	public:
	//constructor, destructor, assignment
	// default constructor
	explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _cap(0), _data() {};

	//fill constructor
	explicit vector (size_type n, const T& val = T(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _cap(n), _data(_alloc.allocate(n)) {
		for (size_type i = 0; i < _size; i++) {
			_alloc.construct(&_data[i], val);
		}
	}

	//range constructor
	vector (iterator first, iterator last, const allocator_type& alloc = allocator_type()) :
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

	//destructor
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
		if (_cap < v._cap) {
			this->~vector<T>();
			_data = _alloc.allocate(v._cap);
			_cap = v._cap;
		}
		//https://www.cplusplus.com/reference/vector/vector/operator=/
		//The container preserves its current allocator, which is used to allocate storage in case of reallocation.
		_size = v._size;
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
		return reverse_iterator(_data -1);
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator(_data -1);
	}

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
			size_t newcap = _cap;
			if (n > _cap)
				newcap = std::max(n, _cap * 2);
			reserve(newcap);
			for (size_type i = _size; i < n; i++) {
				_data[i] = val;
			}
			_size = n;
			_cap = newcap;
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

	//assign range
	template <class InputIterator>
		void assign (InputIterator first, InputIterator last) {
			if (!(first < last) && !(first == last)) {
				throw std::length_error("vector");
			}
			reserve(last - first);
			_size = last - first;
			for (size_type i = 0; first < last; first++) {
				_data[i++] = *first;
			}
		}

	//assign fill
	void assign (size_type n, const value_type& val) {
		reserve(n);
		_size = n;
		for (size_type i = 0; i < n; i++) {
			_data[i] = val;
		}
	}


	void push_back (const value_type& val) {
		if (_cap == _size) {
			if (_cap == 0)
				reserve(1);
			else if (_cap * 2 <= max_size())
				reserve(_cap * 2);
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

	//single element
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

	//fill
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

	//range
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

	//single
	iterator erase (iterator position) {
		iterator position_copy = position;
		_size --;
		for (;position < end(); position++) {
			*position = *(position + 1);
		}
		return position_copy;
	}

	//range
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
		resize(0);
	}

	//Allocator
	allocator_type get_allocator() const {
		return _alloc;
	}
};

//relational operators
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

//swap
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
	x.swap(y);
}

} //namespace ft
#endif
