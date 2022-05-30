#ifndef NODE_ITERATOR_HPP
#define NODE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

struct bidirectional_iterator_tag {};
template <class T, class Alloc>
struct Avlnode;

template <typename T, class Compare, class Alloc, class Pointer = T*, class Reference = T& >
class node_iterator : public general_iterator<bidirectional_iterator_tag, Avlnode<T, Alloc> > {
	typedef general_iterator<bidirectional_iterator_tag, Avlnode<T, Alloc> > base_type;
	private:
	typename base_type::pointer _pointer;
	public:
	//Constructors 
	node_iterator(typename base_type::pointer p) : _pointer(p) {}
	node_iterator() : _pointer(NULL) {}
	//TODO copy constructor
	
	//Copy assignment
	node_iterator &operator=(const node_iterator &it) {
		_pointer = it._pointer;
		return *this;
	}
	//Destructor 
	~node_iterator() {}

	//Comparison
	bool operator == (const node_iterator &nodei) const { return _pointer == nodei._pointer; }
	bool operator != (const node_iterator &nodei) const { return _pointer != nodei._pointer; }

	//Dereference
	//https://stackoverflow.com/questions/21569483/c-overloading-dereference-operators
	T* operator->() const { return &(_pointer->_elem); }
	T& operator*() const { return _pointer->_elem; }

	//increment
	node_iterator &operator++() {
		_pointer = _pointer->next();
		return *this;
	}
	node_iterator operator++(int) {
		node_iterator tmp = *this;
		_pointer = _pointer->next();
		return tmp;
	}

	//decrement
	node_iterator &operator--() {
		_pointer = _pointer->previous();
		return *this;
	}
	node_iterator operator--(int) {
		node_iterator tmp = *this;
		_pointer = _pointer->previous();
		return tmp;
	}

	/*implicit conversion*/
	operator node_iterator< T, Compare, Alloc, const T*, const T&> () const {
		return (node_iterator< T, Compare, Alloc, const T*, const T&>(_pointer));
	}
};

//https://www.cplusplus.com/reference/iterator/reverse_iterator/
template <typename T, class Compare, class Alloc, class Pointer = T*, class Reference = T& >
class rev_node_iterator : public general_iterator<bidirectional_iterator_tag, Avlnode<T, Alloc> > {
	typedef general_iterator<bidirectional_iterator_tag, Avlnode<T, Alloc> > base_type;
	private:
	node_iterator<T, Compare, Alloc> _base;
	public:
	//constructors
	rev_node_iterator(typename base_type::pointer p) : _base(p) { }
	rev_node_iterator() : _base(NULL) { }
	rev_node_iterator(node_iterator<T, Compare, Alloc> b) : _base(b) { }
	// copy constructor
	template <class E>
	rev_node_iterator(const rev_node_iterator<E, Compare, Alloc> &it) : _base(it.base()) {}
	//copy assignment
	rev_node_iterator &operator=(const rev_node_iterator &it) {
		_base = it._base;
		return *this;
	}
	//Base!
	rev_node_iterator base() const {return _base;}

	//Destuctor
	~rev_node_iterator() {};

	//dereference
	//https://stackoverflow.com/questions/21569483/c-overloading-dereference-operators
	T* operator->() const { return &(*_base); }
	T& operator*() const { return *_base; }

	bool operator == (const rev_node_iterator &nodei) const { return _base == nodei._base; }
	bool operator != (const rev_node_iterator &nodei) const { return _base != nodei._base; }

	//increment
	rev_node_iterator &operator++() {
		_base--;
		return *this;
	}
	rev_node_iterator operator++(int) {
		rev_node_iterator tmp = *this;
		_base--;
		return tmp;
	}	

	//decrement
	rev_node_iterator &operator--() {
		_base++;
		return *this;
	}
	rev_node_iterator operator--(int) {
		rev_node_iterator tmp = *this;
		_base++;
		return tmp;
	}

	/*implicit conversion!*/
	operator rev_node_iterator< T, Compare, Alloc, const T*, const T&> () const {
		return (rev_node_iterator< T, Compare, Alloc, const T*, const T&>(_base));
	}
};

}

#endif
