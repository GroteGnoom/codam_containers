#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP


namespace ft {

struct random_access_iterator_tag {};

template <typename T, typename Distance>
class ra_iterator : public general_iterator<random_access_iterator_tag, T, Distance> {
#define op(a) bool operator a (const const_iter &rai) const { return _pointer a rai._pointer; }
	typedef general_iterator<random_access_iterator_tag, T, Distance> base;
	private:
		typedef ra_iterator<const T, Distance> const_iter;
	public:
		typename base::pointer _pointer;
		//coplien
		ra_iterator() : _pointer(NULL) {} //TODO remove
		ra_iterator(typename base::pointer pointer) : _pointer(pointer) {}
		ra_iterator(const ra_iterator &it) : _pointer(it._pointer) {}
		ra_iterator &operator=(const ra_iterator &it) {
			_pointer = it._pointer;
			return *this;
		}
		//equivalence
		op(==)
		op(!=)
		
		//dereference
		T* operator->() const { return _pointer; }
		T& operator*() const { return *_pointer; }

		//increment
		ra_iterator &operator++() {
			_pointer += 1;
			return *this;
		}
		ra_iterator operator++(int) {
			ra_iterator tmp = *this;
			_pointer += 1;
			return tmp;
		}

		//decrement
		ra_iterator &operator--() {
			_pointer -= 1;
			return *this;
		}
		ra_iterator operator--(int) {
			ra_iterator tmp = *this;
			_pointer -= 1;
			return tmp;
		}

		//arithmetic
		ra_iterator operator+(Distance a) const {
			ra_iterator i = *this;
			i._pointer += a;
			return i;
		}
		// reverse addition is outside of class
		ra_iterator operator-(Distance a) const {
			ra_iterator i = *this;
			i._pointer -= a;
			return i;
		}
		// reverse subtraction is outside of class

		//compound assignment
		ra_iterator &operator+=(Distance a) {
			_pointer += a;
			return *this;
		}

		ra_iterator &operator-=(Distance a) {
			_pointer -= a;
			return *this;
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
		operator const_iter () const
		{
			return (const_iter(_pointer));
		}

		op(<)
		op(>)
		op(<=)
		op(>=)
#undef op
};

template <typename T, typename Distance>
class rev_ra_iterator : public general_iterator<random_access_iterator_tag, T, Distance> {
	typedef general_iterator<random_access_iterator_tag, T, Distance> base;
	private:
	public:
		typename base::pointer _pointer;
		rev_ra_iterator(typename base::pointer p) : _pointer(p) {}
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
		rev_ra_iterator operator++(int) {
			rev_ra_iterator tmp = *this;
			_pointer -= 1;
			return tmp;
		}
		rev_ra_iterator &operator--() {
			_pointer += 1;
			return *this;
		}
		rev_ra_iterator operator--(int) {
			rev_ra_iterator tmp = *this;
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

}

#endif
