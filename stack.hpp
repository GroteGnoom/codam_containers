#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef> //NULL
#include <memory> /* allocator */
#include <iostream>
#include "iterator.hpp"
#include "vector.hpp"

namespace ft {

template <class T, class Container = vector<T> > class stack {
	protected:
	Container c;
	public:
	//Member types
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;

	//constructor
	explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {};


	bool empty() const {return c.empty();}

	size_type size() const {return c.size();};

	value_type& top() {return *(c.end() - 1);};
	const value_type& top() const {return *(c.end() - 1);};

	void push (const value_type& val) {c.push_back(val);};

	void pop() {c.pop_back();};
	//these need to be friends to prevent
	//error: 'c' is a protected member of 'ft::stack<std::string>'
	//ft:: before the operator is necessary to indicate it's outside of the class
#define op(a) friend bool ft::operator a (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	op(==)
	op(!=)
	op(<)
	op(<=)
	op(>)
	op(>=)
#undef op
	//Another way to fix this is to have the operators as members directly:
	//https://stackoverflow.com/questions/23335209/error-overloaded-operator-must-be-a-binary-operator-has-3-parameters
	//https://www.reddit.com/r/cpp_questions/comments/3lc6om/operator_must_be_a_binary_operator_has_3/
	//#define op(a) bool operator a (const stack& rhs) { return c a rhs.c; }
};

//Non-member function overloads
#define op(a) template <class T, class Container> bool operator a (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c a rhs.c; }

op(==)
op(!=)
op(<)
op(<=)
op(>)
op(>=)

}

#endif
