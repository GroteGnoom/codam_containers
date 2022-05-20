#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef> //NULL
#include <memory> /* allocator */
#include <iostream>
#include "iterator.hpp"
#include "vector.hpp"

namespace ft {

template <class T, class Container = vector<T> > class stack {
	public:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;
	Container _ctnr;
	explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {};
	bool empty() const {return _ctnr.empty();}
	size_type size() const {return _ctnr.size();};
	value_type& top() {return *(_ctnr.end() - 1);};
	const value_type& top() const {return *(_ctnr.end() - 1);};
	void push (const value_type& val) {_ctnr.push_back(val);};
	void pop() {_ctnr.pop_back();};
};

#define op(a) template <class T, class Container> bool operator a (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._ctnr a rhs._ctnr; }

op(==)
op(!=)
op(<)
op(<=)
op(>)
op(>=)

}
#endif
