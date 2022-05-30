#ifndef MAP_HPP
#define MAP_HPP
#include <algorithm> /*max*/
#include <iostream> //TODO remove
#include <assert.h> //TODO remove
#include <cstddef>
#include <memory> /* allocator */
#include "node_iterator.hpp"
#include "pair.hpp"
namespace ft {

template <class T, class Alloc>
struct Avlnode {
	T _elem;
	Avlnode *_left;
	Avlnode *_right;
	Avlnode *_parent;
	Avlnode *_begin_sentinel;
	Avlnode *_end_sentinel;
	Avlnode(T elem, Avlnode *parent, Avlnode *begin_sentinel, Avlnode *end_sentinel) : _elem(elem), _left(NULL), _right(NULL), _parent(parent), _begin_sentinel(begin_sentinel), _end_sentinel(end_sentinel) {}
	Avlnode(Avlnode *root, Avlnode *begin_sentinel, Avlnode *end_sentinel) : _elem(T()), _left(NULL), _right(NULL), _parent(root), _begin_sentinel(begin_sentinel), _end_sentinel(end_sentinel) {}
	typename Alloc::template rebind<Avlnode>::other node_alloc;
	Avlnode(const Avlnode &a) : _elem(a._elem), _left(a._left), _right(a._right), _parent(a._parent), _begin_sentinel(a._begin_sentinel), _end_sentinel(a._end_sentinel) {
	}
	Avlnode &operator=(const Avlnode &a) {
		_elem = a._elem;
		_left = a._left;
		_right = a._right;
		_parent = a._parent;
		return *this;
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
		Avlnode *a = this;
		while (a->_parent)
			a = a->_parent;
		return a;
	}
	const Avlnode *root() const {
		Avlnode *a = this;
		while (a->_parent)
			a = a->_parent;
		return a;
	}
	void left_rotate() {
		Avlnode *y = _right;
		assert(y);
		this->_right = y->_left;
		if (this->_parent)
		{
			if (this->_parent->_left == this) {
				this->_parent->_left = y;
			} else {
				this->_parent->_right = y;
			}
		}
		y->_parent = this->_parent;
		y->_left = this;
		this->_parent = y;
		if (this->_right)
			this->_right->_parent = this;
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
		if (this->_left)
			this->_left->_parent = this;
	}
	Avlnode *newnode(T elem) {
		Avlnode *node = node_alloc.allocate(1);
		node_alloc.construct(node, Avlnode(elem, this, _begin_sentinel, _end_sentinel));
		return node;
	}
	void del() {
			this->~Avlnode();
			node_alloc.deallocate(this, 1);
	}
	void del_children() {
		if (_left) {
			_left->del_children();
			_left->del();
			_left = NULL;
		}
		if (_right) {
			_right->del_children();
			_right->del();
			_right = NULL;
		}
	}
	Avlnode *end() {
		return _end_sentinel;
	}
	Avlnode *rbegin() {
		Avlnode *current = root();
		while (current->_right)
			current = current->_right;
		return current;
	}
	Avlnode *rend() {
		return _begin_sentinel;
	}
	Avlnode *begin() {
		Avlnode *current = root();
		while (current->_left)
			current = current->_left;
		return current;
	}
	Avlnode *next() {
		if (this == rend()) {
			return begin();
		}
		Avlnode *current = this;
		if (_right) {
			current = _right;
			while (current->_left) {
				current = current->_left;
			}
			return current;
		}
		while (true) {
			if (!current->_parent) {
				return end();
			}
			if (current->_parent->_left == current) {
				return current->_parent;
			}
			current = current->_parent;
		}
	}
	Avlnode *previous() {
		if (this == begin()) {
			return rend();
		}
		if (this == end()) {
			return rbegin();
		}
		Avlnode *current = this;
		if (_left) {
			current = _left;
			while (current->_right) {
				current = current->_right;
			}
			return current;
		}
		while (true) {
			if (!current->_parent)
				return rend();
			if (current->_parent->_right == current) {
				return current->_parent;
			}
			current = current->_parent;
		}
	}
	size_t size() const {
		size_t lsize = 0;
		size_t rsize = 0;
		if (_left)
			lsize = _left->size();
		if (_right)
			rsize = _right->size();
		return 1 + lsize + rsize;
	}
	void after_erase_balance() {
		if (get_balance() > 1) {
			if (_left->get_balance() >= 0) {
				right_rotate();
				return;
			}
			_left->left_rotate();
			right_rotate();
		} else if (get_balance() < -1) {
			if (_right->get_balance() <= 0) {
				left_rotate();
				return;
			}
			_right->right_rotate();
			left_rotate();
		}
	}
	Avlnode *erase() {
		/*returns root*/
		Avlnode* parent = _parent;
		Avlnode* start_balance = _parent;
		//https://stackoverflow.com/questions/3150942/is-delete-this-allowed-in-c9
		if (!_left && !_right) {
			if (parent && parent->_left == this) {
				parent->_left = NULL;
			}
			else if (parent && parent->_right == this)
				parent->_right = NULL;
			this->del();
		} else if (!_left) {
			if (!parent) {
				_right->_parent = NULL;
				Avlnode *right = _right;
				this->del();
				return right;
			} else if (parent->_left == this) {
				parent->_left = _right;
				_right->_parent = parent;
			}
			else if (parent->_right == this) {
				parent->_right = _right;
				_right->_parent = parent;
			}
			this->del();
		} else if (!_right) {
			if (!parent) {
				_left->_parent = NULL;
				Avlnode *left = _left;
				this->del();
				return left;
			} else if (parent->_left == this) {
				parent->_left = _left;
				_left->_parent = parent;
			}
			else if (parent->_right == this) {
				parent->_right = _left;
				_left->_parent = parent;
			}
			this->del();
		} else {
			Avlnode *next = _right;
			int steps = 0;
			while (next->_left) {
				steps = 1;
				next = next->_left;
			}
			if (steps) {
				next->_parent->_left = NULL;
			} else {
				next->_parent->_right = NULL;
			}
			/* next goes in place of this */
			/* I can't replace the internals (like with copy assigment) easily
			   because the default allocator uses a const key*/
			if (!parent) {
				next->_parent = NULL;
			} else if (parent->_left == this) {
				parent->_left = next;
				next->_parent = parent;
			} else if (parent->_right == this) {
				parent->_right = next;
				next->_parent = parent;
			}
			next->_left = _left;
			next->_right = _right;
			this->del();
			start_balance = next;
		}
		if (start_balance) {
			start_balance->after_erase_balance();
			return start_balance->root();
		} else {
			/*removed root*/
			return NULL;
		}
	}
};

template < class Key,
 class T,
 class Compare = std::less<Key>,
// class Alloc = std::allocator<pair<const Key,T> > >
 class Alloc = std::allocator<pair<const Key,T> > >

class map {
	public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	class value_compare : std::binary_function<value_type, value_type, bool> {
		friend class map;
		protected:
		Compare comp;
		value_compare (Compare c = Compare()) : comp(c) {}
		public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
			/*this was my old way of doing things:*/
			//return Compare()(x.first, y.first);
		}
	};
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef node_iterator<value_type, Alloc> iterator;
	typedef node_iterator<value_type, Alloc, const value_type *, const value_type &> const_iterator;
	typedef rev_node_iterator<value_type, Alloc> reverse_iterator;
	typedef rev_node_iterator<value_type, Alloc, const value_type *, const value_type &> const_reverse_iterator;
	private:
	key_compare _comp;
	allocator_type _alloc;
	typedef Avlnode<value_type, Alloc> node;
	value_compare vc;
	//start tree
	typename Alloc::template rebind<node>::other node_alloc;
	Avlnode<value_type, Alloc> *_root;
	node *_begin_sentinel;
	node *_end_sentinel;
	node *newroot(value_type elem ) {
		node *np = node_alloc.allocate(1);
		node n(elem, NULL, _begin_sentinel, _end_sentinel);
		node_alloc.construct(np, n);
		_begin_sentinel->_parent = np;
		_end_sentinel->_parent = np;
		return np;
	}
	node *newsentinel(value_type elem ) {
		node *np = node_alloc.allocate(1);
		node n(elem, NULL, NULL, NULL);
		node_alloc.construct(np, n);
		return np;
	}
	void reroot() {
		_root = _root->root();
		_begin_sentinel->_parent = _root;
		_end_sentinel->_parent = _root;
	}
	void rebalance(node *new_node) {
		int balance;
		node *parent = new_node->_parent;
		if (!parent) return;
		node *grandparent = parent->_parent;
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
			if (new_node->_elem > parent->_elem) {
				return grandparent->left_rotate();
			} else {
				parent->right_rotate();
				return grandparent->left_rotate();
			}
		}
	}
	node* tree_insert(value_type elem) {
		if (!_root) {
			_root = newroot(elem);
			return _root;
		}
		node *current = _root;
		while (true) {
			if (vc(elem, current->_elem)) {
				if (current->_left) {
					current = current->_left;
				}
				else {
					current->_left = current->newnode(elem);
					current = current->_left;
					break;
				}
			} else {
				if (current->_right) {
					current = current->_right;
				}
				else {
					current->_right = current->newnode(elem);
					current = current->_right;
					break;
				}
			}
		}
		reroot();
		rebalance(current);
		reroot();
		return current;
	}
	node *tree_begin() const {
		if (!_root) return NULL;
		node *search = _root;
		while (search->_left) {
			search = search->_left;
		}
		return search;
	}
	node *tree_end() const {
		if (!_root) return tree_begin();
		return _end_sentinel;
	}
	node *tree_rbegin() const {
		if (!_root) return tree_begin();
		node *search = _root;
		while (search->_right) {
			search = search->_right;
		}
		return search;
	}
	node *tree_rend() const {
		if (!_root) return tree_begin();
		return _begin_sentinel;
	}
	node *tree_find(const value_type a) const {
		if (!_root)
			return tree_end();
		node *found = NULL;
		node *current = _root;
		while (true) {
			if (vc(a, current->_elem)){
				if (!current->_left)
					break;
				current = current->_left;
			} else if (vc(current->_elem, a)){
				if (!current->_right)
					break;
				current = current->_right;
			} else {
				found = current;
				break;
			}
		}
		if (found)
			return found;
		return tree_end();
	}
	node *lower_bound(const value_type a) const {
		//std::cout << "start of lower bound\n";
		if (!_root) return tree_end();
		//std::cout << "there's a root\n";
		node *current = _root;
		//std::cout << "current elem before loop: " << current->_elem.first << "\n";
		while (vc(current->_elem, a)) {
			//std::cout << "current elem:" << current->_elem << "\n";
			if (!current->_right)
				return tree_end();
			current = current->_right;
		}
		//std::cout << "found upper bound: " << current->_elem << "\n";
		node *found = current;
		while (true) {
			if (vc(a, current->_elem))
			{
				if (current->_left)
					current = current->_left;
				else
					break;
			}
			else if (vc(current->_elem, a))  {
				if (current->_right)
					current = current->_right;
				else break;
			}
			else
				return current;
			if (vc(current->_elem, found->_elem)
					&& vc(a, current->_elem))
				found = current;
		}
		return found;
	}
	/* not the reverse of upper bound, this needs to be strictly after a */
	/* can also only use this function, and make lower bound a combination of upper_bound and find */
	node *upper_bound(const value_type a) const {
		if (!_root) return tree_end();
		node *current = _root;
		while (!vc(a, current->_elem)) {
			if (!current->_right)
				return tree_end();
			current = current->_right;
		}
		node *found = current;
		while (true) {
			if (vc(a, current->_elem))
			{
				if (current->_left)
					current = current->_left;
				else
					break;
			}
			else {
				if (current->_right)
					current = current->_right;
				else break;
			}
			if (vc(current->_elem, found->_elem)
					&& vc(a, current->_elem))
				found = current;
		}
		return found;
	}
	void tree_clear() {
		if (!_root) return;
		_root->del_children();
		_root->del();
		_root = NULL;
	}
	void init() {
		_root = NULL;
		_begin_sentinel = newsentinel(value_type());
		_end_sentinel = newsentinel(value_type());
		_begin_sentinel->_begin_sentinel = _begin_sentinel;
		_begin_sentinel->_end_sentinel = _end_sentinel;
		_end_sentinel->_begin_sentinel = _begin_sentinel;
		_end_sentinel->_end_sentinel = _end_sentinel;
	}
	//end tree
	public:
	explicit map (const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) {
		init();
	};
	template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) {
			init();
			for (; first != last; first++) {
				insert(*first);
			}
		}
	~map() {
		 _begin_sentinel->del();
		 _end_sentinel->del();
		 clear();
	}
	map (const map& x) : _comp(x._comp), _alloc(x._alloc) {
		init();
		for (const_iterator first = x.begin(); first != x.end(); first++) {
			insert(*first);
		}
	}
	map& operator= (const map& x) {
		tree_clear();
		for (const_iterator i = x.begin(); i != x.end(); i++) {
			insert(*i);
		}
		return *this;
	};
	iterator begin() {return tree_begin();};
	const_iterator begin() const {
		node *n = tree_begin();
		return const_iterator(n);
	}
	iterator end() {return tree_end();};
	const_iterator end() const {return iterator(tree_end());};

	reverse_iterator rbegin() {return (tree_rbegin());};
	const_reverse_iterator rbegin() const {return tree_rbegin();};
	reverse_iterator rend() {return tree_rend();};
	const_reverse_iterator rend() const {return iterator(tree_rend());};

	bool empty() const {return !_root;}
	size_type size() const {
		if (empty()) return 0;
		return _root->size();
	}
	size_type max_size() const {return std::numeric_limits<size_type>::max() / sizeof(node);}
	//Modifiers
	pair<iterator,bool> insert (const value_type& val) {
		if (!empty()) {
			iterator already_exists = tree_find(val);
			if (already_exists != end()) {
				pair<iterator, bool> retval(already_exists, false);
				return retval;
			}
		}
		iterator inserted = tree_insert(val);
		pair<iterator, bool> retval(inserted, true);
		return retval;
	}
	iterator insert (iterator position, const value_type& val) {
		(void) position;
		//TODO hint?
		pair<iterator,bool> p = insert(val);
		return p.first;
	}
	template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (;first != last; first++) {
				insert(*first);
			}
		}
	mapped_type &operator[] (const key_type &k) {
		pair<iterator,bool> inserted = insert(pair<key_type, mapped_type>(k,mapped_type()));
		return (*(inserted.first)).second;
	}
	void erase (iterator position) {
		node *p = reinterpret_cast<node *>(&(*position));
		_root = p->erase();
		//std::cout << "new root: " << _tree._root->_elem << "\n";
		//_tree.reroot();
	}
	void erase (iterator first, iterator last) {
		//TODO proper solution
		key_type* keys = new key_type[size()];
		int i = 0;
		for (;first != last; first++) {
			keys[i] = first->first;
			i++;
		}
		for (i = i - 1;i >= 0; i--) {
			erase(keys[i]);
		}
		delete[] keys;
	};
	iterator find (const key_type& k) {
		return tree_find(pair<key_type, mapped_type>(k,mapped_type()));
	}
	const_iterator find (const key_type& k) const {
		const pair<key_type, mapped_type> p(k,mapped_type());
		return const_iterator(tree_find(p));
		//const Avlnode<value_type> *r = reinterpret_cast<const Avlnode<value_type> *>(_tree.find(p));
		//return r;
	}

	size_type erase (const key_type& k) {
		iterator i = find(k);
		if (i == end())
			return 0;
		erase(i);
		return 1;
	}

	 void swap (map& x) {
		 node *s = _root;
		 _root = x._root;
		 x._root = s;
		 s = _begin_sentinel;
		 _begin_sentinel = x._begin_sentinel;
		 x._begin_sentinel = s;
		 s = _end_sentinel;
		 _end_sentinel = x._end_sentinel;
		 x._end_sentinel = s;
	 }
	//https://stackoverflow.com/questions/14187006/is-calling-destructor-manually-always-a-sign-of-bad-design
	 void clear() {
		 tree_clear();
	 }
	 key_compare key_comp() const {
		 return _comp;
	 };
	 value_compare value_comp() const {
		 return value_compare(key_comp());
	 }
	 size_type count (const key_type& k) const {
		const_iterator i = find(k);
		if (i == end())
		 return 0;
		return 1;
	 };
	 const_iterator lower_bound (const key_type& k) const {
		return lower_bound(value_type(k, mapped_type()));
	 }
	 iterator lower_bound (const key_type& k) {
		return lower_bound(value_type(k, mapped_type()));
	 }
	 const_iterator upper_bound (const key_type& k) const {
		return upper_bound(value_type(k, mapped_type()));
	 }
	 iterator upper_bound (const key_type& k) {
		return upper_bound(value_type(k, mapped_type()));
	 }
	 pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
		 const_iterator i = find(k);
		 if (i != end()) {
			 return pair<const_iterator,const_iterator>(i, upper_bound(k));
		 }
		 return pair<const_iterator,const_iterator>(upper_bound(k), upper_bound(k));
	 }
	 pair<iterator, iterator> equal_range (const key_type& k) {
		 iterator i = find(k);
		 if (i != end()) {
			 return pair<iterator,iterator>(i, upper_bound(k));
		 }
		 return pair<iterator,iterator>(upper_bound(k), upper_bound(k));
	 }
	 allocator_type get_allocator() const {return _alloc;};
}; //map
} //namespace
#endif
