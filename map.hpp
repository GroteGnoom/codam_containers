#ifndef MAP_HPP
#define MAP_HPP
#include <algorithm> /*max*/
#include <iostream> //TODO remove
#include <assert.h> //TODO remove
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
	Avlnode(T elem, Avlnode<T> *parent) {
		_left = NULL;
		_right = NULL;
		_parent = parent;
		_elem = elem;
	}
	int get_height() const {
		int lheight = 0;
		int rheight = 0;
		if (_left)
			lheight = _left->get_height();
		if (_right)
			rheight = _right->get_height();
		return 1 + std::max(lheight, rheight);
	}
	int get_balance() const {
		int lheight = 0;
		int rheight = 0;
		if (_left)
			lheight = _left->get_height();
		if (_right)
			rheight = _right->get_height();
		return lheight - rheight;
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
		Avlnode *parent = _parent;
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
		if (parent)
		{
			if (parent->_left == this) {
				parent->_left = y;
			} else {
				parent->_right = y;
			}
		}
	}
	void right_rotate() {
		Avlnode *parent = _parent;
		Avlnode *y = this;
		Avlnode *x = _left;
		if (!x) return;
		y->_left = x->_right;
		x->_right = y;
		x->_parent = y->_parent;
		y->_parent = x;
		if (parent)
		{
			if (parent->_left == this) {
				parent->_left = x;
			} else {
				parent->_right = x;
			}
		}
	}
	Avlnode<T> *insert(T elem) {
		if (elem < _elem) {
			if (_left) {
				return _left->insert(elem);
			}
			else {
				_left = new Avlnode(elem, this);
				return _left;
			}
		} else {
			if (_right)
				return _right->insert(elem);
			else {
				_right = new Avlnode(elem, this);
				return _right;
			}
		}
	}
	void del_children() {
		if (_left) {
			_left->del_children();
			delete _left;
			_left = NULL;
		}
		if (_right) {
			_right->del_children();
			delete _right;
			_right = NULL;
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
				Avlnode<T> *new_node = _root->insert(elem);
				_root = _root->root();
				rebalance(new_node);
				_root = _root->root();
			}
		}
		~Avltree() {
			_root->del_children();
			delete _root;
			_root = NULL;
		}
	private:
		void rebalance(Avlnode<T> *new_node) {
			int balance;
			Avlnode<T> *parent = new_node->_parent;
			if (!parent) return;
			Avlnode<T> *grandparent = parent->_parent;
			if (!grandparent) return;
			balance = grandparent->get_balance();
			//std::cout << "balance" << balance << "\n";
			if (balance > 1) {
				if (new_node->_elem < parent->_elem) {
					return grandparent->right_rotate();
				} else {
					parent->left_rotate();
					return grandparent->right_rotate();
				}
			} else if (balance < -1)  {
				//std::cout << "right is longer\n";
				if (new_node->_elem > parent->_elem) {
					//std::cout << "doing left rotate\n";
					return grandparent->left_rotate();
				} else {
					//std::cout << "doing right left rotate\n";
					parent->right_rotate();
					return grandparent->left_rotate();
				}
			}
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
