#ifndef MAP_HPP
#define MAP_HPP

#include <cstddef>
#include <memory> /* allocator */
namespace ft {


template <class T1, class T2>
struct pair{};

template <class T>
struct Avlnode {
	T _elem;
	Avlnode *_left;
	Avlnode *_right;
	Avlnode *_parent;
	int height;
	Avlnode(T elem, Avlnode<T> *parent) {
		_left = NULL;
		_right = NULL;
		_parent = parent;
		_elem = elem;
	}
	static int get_height(Avlnode *node) {
		if (node)
			return node->height;
		return 0;
	}
	void set_height() {
		height = get_height(_left) + get_height(_right);
		if (_parent)
			_parent->set_height();
	}
	Avlnode *root() {
		Avlnode *a = this;;
		while (a->_parent)
			a = a->_parent;
		return a;
	}
	void left_rotate() {
		Avlnode *x = this;
		Avlnode *y = _right;
		/*
		if (!y) return;
		if (y->left) {
			x->right = y->left;
			x->right.parent = x;
		}
		if (!x->parent)
			y->parent = NULL;
		else if (x == x->parent->left)
		{
			x->parent->left = y;
			y->parent = x->parent;
		} else {
			x->parent->right = y;
			y->parent = x->parent;
		}
		y->left = x;
		x->parent = y;
		*/
		if (!y) return;
		x->_right = y->_left;
		y->_left = x;
		y->_parent = x->_parent;
		x->_parent = y;
		x->set_height();
		y->set_height();
	}
	void right_rotate() {
		Avlnode *x = this;
		Avlnode *y = _left;
		if (!y) return;
		x->_left = y->_right;
		y->_right = x;
		y->_parent = x->_parent;
		x->_parent = y;
		x->set_height();
		y->set_height();
	}
	void insert2(T elem) {
		if (elem < _elem) {
			if (_left) {
				_left->insert2(elem);
			}
			else {
				_left = new Avlnode(elem, this);
				_left->set_height();
			}
		} else {
			if (_right)
				_right->insert2(elem);
			else {
				_right = new Avlnode(elem, this);
				_right->set_height();
			}
		}
	}
	void insert(T elem) {
		root()->insert2(elem);
	}
	void del() {
		if (_left) {
			_left->del();
			delete _left;
		}
		if (_right) {
			_right->del();
			delete _right;
		}
	}
};

template <class T>
class Avltree {
	public:
		Avlnode<T> *_root;
		Avltree() : _root(NULL) {}
		void insert(T elem) {
			if (!_root) {
				_root = new Avlnode<T>(elem, NULL);
			} else {
				_root->insert(elem);
				_root = _root->root();
			}
		}
		~Avltree() {
			_root->del();
			delete _root;
			_root = 0;
		}
};

template < class Key,
		 class T,
		 class Compare = std::less<Key>,
		 class Alloc = std::allocator<pair<const Key,T> > >

class map {
	public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	class value_compare {}; //TODO
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	//TODO iterator
	//TODO const_iterator
	//TODO reverse_itarator
	//TODO const_reverse_iterator
	typedef std::ptrdiff_t difference_type;
	typedef size_t size_type;

	explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()); //TODO 


};
}
#endif
