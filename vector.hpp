#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef> //NULL
#include <memory> /* allocator */
#include <iostream>

namespace ft {

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct general_iterator {
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
	typedef Category  iterator_category;
};

template <typename T, typename Distance>
class ra_iterator : general_iterator<std::random_access_iterator_tag, T, Distance> {
	typedef general_iterator<std::random_access_iterator_tag, T, Distance> base;
	private:
		typename base::pointer _pointer;
	public:
		ra_iterator(typename base::pointer p) : _pointer(p) {}
		ra_iterator &operator+(Distance a) {
			_pointer += a;
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
		ra_iterator &operator-(Distance a) {
			_pointer -= a;
			return *this;
		}
		typename base::difference_type operator-(const ra_iterator &rai) {
			return _pointer - rai._pointer;
		}

		bool operator<(const ra_iterator &rai) {
			return _pointer < rai._pointer;
		}

		bool operator==(const ra_iterator &rai) {
			return _pointer == rai._pointer;
		}

		bool operator>(const ra_iterator &rai) {
			return _pointer > rai._pointer;
		}

		T &operator*() const {
			return *_pointer;
		}
};

template <typename T, typename Alloc = std::allocator<T> >
class vector {
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef size_t size_type;
	typedef ra_iterator<T, size_type> iterator;
	//typedef reverse_ra_iterator<T, size_type> reverse_iterator;
	private:
		allocator_type _alloc;
		size_type _size;
		size_type _cap;
		T *_data;
	public:
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
				for (size_type i = 0; i < _size; i++) {
					_data[i].~T();
				}
				_size = 0;
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
		iterator end() {
			return begin() + _size;
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
		bool empty() { return !_size; }
		void reserve(size_type n) {
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
		T& operator[](const size_type idx) { return _data[idx]; }

		const T& operator[](const size_type idx) const { return _data[idx]; }

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
				if (_cap * 2 <= max_size())
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

		iterator insert (iterator position, const value_type& val) {
			iterator position_copy = position;
			resize(_size + 1);
			T s = val;
			for (; position < end(); position++) {
				T n = *position;
				*position = s;
				s = n;
			}
			return position_copy;
		}

		void insert (iterator position, size_type n, const value_type& val) {
			size_type start = position - begin();
			resize(_size + n);
			for (size_type i = _size - 1; i >= _size - n ; i--) {
				_data[i] = _data[i - n];
			}
			for (size_type i = 0; i < n ; i++) {
				(*this)[start + i] = val;
			}
		}
};


} //namespace ft
#endif
