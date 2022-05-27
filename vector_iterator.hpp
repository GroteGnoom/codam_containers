#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP


namespace ft {

struct random_access_iterator_tag {};

/*
template <typename T, typename Distance>
class ra_iterator : public general_iterator<random_access_iterator_tag, T, Distance> {
#define op(a) bool operator a (const const_iter &rai) const { return _pointer a rai._pointer; }
	typedef general_iterator<random_access_iterator_tag, T, Distance> base;
	private:
		typedef ra_iterator<const T, Distance> const_iter;
		typename base::pointer _pointer;
	public:
		//coplien
		ra_iterator() : _pointer(NULL) {}
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
*/

template <typename T>
class rev_ra_iterator : public general_iterator<random_access_iterator_tag, T> {
		T* _base;
		typedef rev_ra_iterator<const T> const_rev_ra_iterator;
		typedef ptrdiff_t Distance;
	public:
		//default constructor
		rev_ra_iterator() : _base() {}

		//https://cplusplus.com/reference/iterator/reverse_iterator/reverse_iterator/
		explicit rev_ra_iterator(T* it) : _base(&(*it)) {};

		template <class Iter>
		rev_ra_iterator(const rev_ra_iterator<Iter> &it) : _base(it.base()) {}
		rev_ra_iterator &operator=(const rev_ra_iterator &it) {
			_base = it._base;
			return *this;
		}
		~rev_ra_iterator() {}
		T* base() const {return _base;}
		T& operator*() const { return *_base; }
		rev_ra_iterator operator+(Distance a) const {
			return rev_ra_iterator(_base - a);
		}
		rev_ra_iterator &operator++() {
			_base -= 1;
			return *this;
		}
		rev_ra_iterator operator++(int) {
			return rev_ra_iterator(_base--);
		}
		rev_ra_iterator &operator+=(Distance a) {
			_base -= a;
			return *this;
		}
		rev_ra_iterator operator-(Distance a) const {
			return rev_ra_iterator(_base + a);
		}
		rev_ra_iterator &operator--() {
			_base += 1;
			return *this;
		}
		rev_ra_iterator operator--(int) {
			return rev_ra_iterator(_base++);
		}
		rev_ra_iterator &operator-=(Distance a) {
			_base += a;
			return *this;
		}
		Distance operator-(const const_rev_ra_iterator &a) const {
			return a.base() - _base;
		}
		T* operator->() const { return _base; }
		T& operator[](size_t idx) {
			return *(_base - idx);
		}
		const T& operator[](size_t idx) const {
			return *(_base - idx);
		}
		operator const_rev_ra_iterator () const
		{
			return (const_rev_ra_iterator(_base));
		}
};

#define op(a, b) template <class Iterator> bool operator a (const rev_ra_iterator<Iterator>& lhs, const rev_ra_iterator<Iterator>& rhs) {return lhs.base() b rhs.base();}
op(<, >)
op(<=, >=)
op(>, <)
op(>=, <=)
op(==, ==)
op(!=, !=)
#undef op

		/*
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
*/

/*
template <typename T, typename Distance>
ra_iterator<T, Distance> operator+(ptrdiff_t a, const ra_iterator<T, Distance> &b) {
	return b + a;
}
*/

template <typename T>
rev_ra_iterator<T> operator+(ptrdiff_t a, const rev_ra_iterator<T> &b) {
	return b + a;
}

template <typename T>
ptrdiff_t operator-(const rev_ra_iterator<T> a, const rev_ra_iterator<T> &b) {
	return b.base() - a.base();
}

}

#endif
