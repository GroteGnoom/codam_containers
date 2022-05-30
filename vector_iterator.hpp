#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP


namespace ft {

struct random_access_iterator_tag {};

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

		T* operator->() const { return _base; }
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
