#ifndef MAP_HPP
#define MAP_HPP
#include <algorithm> /*max*/
#include <iostream> //TODO remove
#include <assert.h> //TODO remove
#include <cstddef>
#include <memory> /* allocator */
#include "iterator.hpp"
namespace ft {

struct bidirectional_iterator_tag {};

template <typename T, typename Distance>
class bi_iterator : public general_iterator<bidirectional_iterator_tag, T, Distance> {
	typedef general_iterator<bidirectional_iterator_tag, T, Distance> base;
	private:
	typename base::pointer _pointer;
	public:
	bi_iterator(const typename base::pointer p) : _pointer(p) {}
	bi_iterator() : _pointer(NULL) {}
	bool operator == (const bi_iterator &bii) const { return _pointer == bii._pointer; }
	bool operator != (const bi_iterator &bii) const { return _pointer != bii._pointer; }
	//TODO operations

	//https://stackoverflow.com/questions/21569483/c-overloading-dereference-operators
	T* operator->() const { return _pointer; }
	T& operator*() const { return *_pointer; }
};

template <class T1, class T2>
struct pair{
	public:
		typedef T1 first_type;
		typedef T2 second_type;
		T1 first;
		T2 second;
		pair() : first(), second() {};

		template<class U, class V>
			pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}
		pair &operator=(const pair<T1, T2> &p) {
			first = p.first;
			second= p.second;
			return *this;
		}
};


template <class T1, class T2>
std::ostream &operator<<(std::ostream &out, const pair<T1,T2> &p) {
	out << "(" << p.first << ", " << p.second << ")";
	return out;
}

//TODO can't I generalize this? you only need less than, and then you're done.
// if a < b || b < a they're not equal, or if !(a<b) && !(b<a) they're equal
template <class T1, class T2>
bool operator== (const pair<T1,T2>& a, const pair<T1,T2>& b) {return a.first == b.first && a.second == b.second;}
template <class T1, class T2>
bool operator!= (const pair<T1,T2>& a, const pair<T1,T2>& b) {return !(a==b);}
//This does a lexicographical comparison, or because there's only two, it checks the first, then the second
template <class T1, class T2>
bool operator< (const pair<T1,T2>& a, const pair<T1,T2>& b) {return (a.first<b.first) || (a.first==b.first && a.second < b.second);}
//The rest follows from equality and less than
template <class T1, class T2>
bool operator<= (const pair<T1,T2>& a, const pair<T1,T2>& b) { return !(b<a); }
template <class T1, class T2>
bool operator>  (const pair<T1,T2>& a, const pair<T1,T2>& b) { return b<a; }
template <class T1, class T2>
bool operator>= (const pair<T1,T2>& a, const pair<T1,T2>& b) { return !(a<b); }


template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
struct Avlnode {
	T _elem; //if this stays as first element, I can easily switch between node and element iterators
	Avlnode *_left;
	Avlnode *_right;
	Avlnode *_parent;
	Avlnode(T elem, Avlnode<T, Compare> *parent) : _elem(elem), _left(NULL), _right(NULL), _parent(parent) {}
	Avlnode(const Avlnode &a) {
		*this = a;
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
	/*
	const Avlnode *root() const {
		const Avlnode *a = this;
		while (a->_parent)
			a = a->_parent;
		return a;
	}
	*/
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
	Avlnode<T, Compare> *insert(T elem) {
		if (Compare()(elem, _elem)) {
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
	T* find(const T a) {
		if (Compare()(a, _elem)){
			if (!_left)
				return NULL;
			return _left->find(a);
		} else if (Compare()(_elem, a)){
			if (!_right)
				return NULL;
			return _right->find(a);
		} else {
			return &_elem;
		}
	}
	const T* find(const T a) const {
		if (Compare()(a, _elem)){
			if (!_left)
				return NULL;
			return _left->find(a);
		} else if (Compare()(_elem, a)){
			if (!_right)
				return NULL;
			return _right->find(a);
		} else {
			return &_elem;
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
	void erase() {
		assert(_parent);
		Avlnode<T>* parent = _parent;
		Avlnode<T>* start_balance = _parent;
		//https://stackoverflow.com/questions/3150942/is-delete-this-allowed-in-c9
		if (!_left && !_right) {
			if (parent->_left == this)
				parent->_left = NULL;
			else if (parent->_right == this)
				parent->_right = NULL;
			delete this;
		} else if (!_left) {
			if (parent->_left == this)
				parent->_left = _right;
			else if (parent->_right == this)
				parent->_right = _right;
			delete this;
		} else if (!_right) {
			if (parent->_left == this)
				parent->_left = _left;
			else if (parent->_right == this)
				parent->_right = _left;
			delete this;
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
			if (parent->_left == this)
				parent->_left = next;
			else if (parent->_right == this) {
				parent->_right = next;
			}
			next->_left = _left;
			next->_right = _right;
			delete (this);
			//std::cout << "parent right" << parent->_right->_elem << "\n";
			//std::cout << "parent right right" << parent->_right->_right->_elem << "\n";
			//std::cout << "parent right left" << parent->_right->_left->_elem << "\n";
			start_balance = next;
		}
		start_balance->after_erase_balance();
	}
	/*
	T* lower_bound(T a) {
		return const_cast<T *>(const_cast <const Avlnode <T, Compare, Alloc> &> (*this).lower_bound(a));
	}
	*/
};

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class Avltree {
	public:
		Avlnode<T, Compare> *_root;
		Avltree() : _root(NULL) {}
		T* insert(T elem) {
			if (!_root) {
				_root = new Avlnode<T, Compare>(elem, NULL);
				return &_root->_elem;
			} else {
				Avlnode<T, Compare> *new_node = _root->insert(elem);
				_root = _root->root();
				rebalance(new_node);
				_root = _root->root();
				return &new_node->_elem;
			}
		}
		~Avltree() {
			if (!_root) return;
			_root->del_children();
			delete _root;
			_root = NULL;
		}
		T* begin() const {
			if (!_root) return NULL;
			Avlnode<T, Compare> *search = _root;

			while (search->_left) {
				search = search->_left;
			}
			return &(search->_elem);
		}
		T* end() const {
			if (!_root) return begin();
			Avlnode<T, Compare> *search = _root;

			while (search->_right) {
				search = search->_right;
			}
			return &(search->_elem) + 1;
		}
		T* find(const T a) {
			if (!_root)
				return end();
			T* found = _root->find(a);
			if (found)
				return found;
			return end();
		}
		const T* find(const T a) const {
			if (!_root)
				return end();
			T* found = _root->find(a);
			if (found)
				return found;
			return end();
		}
		void reroot() {
			_root = _root->root();
		}
		const T* lower_bound(const T a) const {
			//std::cout << "start of lower bound\n";
			if (!_root) return end();
			//std::cout << "there's a root\n";
			const Avlnode<T, Compare, Alloc> *current = _root;
			//std::cout << "current elem before loop: " << current->_elem.first << "\n";
			while (Compare()(current->_elem, a)) {
				//std::cout << "current elem:" << current->_elem << "\n";
				if (!current->_right)
					return end();
				current = current->_right;
			}
			//std::cout << "found upper bound: " << current->_elem << "\n";
			const Avlnode<T, Compare, Alloc> *found = current;
			while (true) {
				if (Compare()(a, current->_elem))
				{
					if (current->_left)
						current = current->_left;
					else
						break;
				}
				else if (Compare()(current->_elem, a))  {
					if (current->_right)
						current = current->_right;
					else break;
				}
				else
					return &(current->_elem);
				if (Compare()(current->_elem, found->_elem)
				&& Compare()(a, current->_elem))
					found = current;
			}
			return &(found->_elem);
		}
		T* lower_bound(const T a) {
			return const_cast<T *>(const_cast <const Avltree <T, Compare, Alloc> &> (*this).lower_bound(a));
		}
		/* not the reverse of upper bound, this needs to be strictly after a */
		/* can also only use this function, and make lower bound a combination of upper_bound and find */
		const T* upper_bound(const T a) const {
			if (!_root) return end();
			const Avlnode<T, Compare, Alloc> *current = _root;
			while (!Compare()(a, current->_elem)) {
				if (!current->_right)
					return end();
				current = current->_right;
			}
			const Avlnode<T, Compare, Alloc> *found = current;
			while (true) {
				if (Compare()(a, current->_elem))
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
				if (Compare()(current->_elem, found->_elem)
				&& Compare()(a, current->_elem))
					found = current;
			}
			return &(found->_elem);
		}
		T* upper_bound(const T a) {
			return const_cast<T *>(const_cast <const Avltree <T, Compare, Alloc> &> (*this).upper_bound(a));
		}
	private:
		void rebalance(Avlnode<T, Compare> *new_node) {
			int balance;
			Avlnode<T, Compare> *parent = new_node->_parent;
			if (!parent) return;
			Avlnode<T, Compare> *grandparent = parent->_parent;
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
};

/*
   template < class Key, class Value, class Compare>
   bool compare_key(pair<Key, Value> p1, pair<Key, Value> p2) {
   return Compare(p1.first, p2.first);
   }
   */

//TODO should inherit from binary_function? Or maybe it doesn't matter because it's only used internally?
template <class Key, class Value, class Compare>
struct compare_key {
	bool operator() (pair<Key, Value> p1, pair<Key, Value> p2) {
		return Compare()(p1.first, p2.first);
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
	 class value_compare : std::binary_function<value_type, value_type, bool> {
		 friend class map;
		 protected:
			 Compare comp;
			 value_compare (Compare c) : comp(c) {}
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
	 //typedef std::bi_iterator<value_type, size_type> iterator;
	 //typedef const bi_iterator<value_type, size_type> const_iterator;
	 typedef value_type * iterator; //TODO should not be just a pointer?
	 typedef const value_type * const_iterator; //TODO
	 //TODO reverse_itarator
	 //TODO const_reverse_iterator
	 Avltree<value_type, compare_key<Key, T, Compare> > _tree; //TODO private, public for debugging
	 private:
	 key_compare _comp;
	 allocator_type _alloc;
	 public:
	 explicit map (const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc(alloc) {};
	 ~map() {};
	 // TODO template <class InputIterator>
	 //	map (InputIterator first, InputIterator last,
	 //			const key_compare& comp = key_compare(),
	 //			const allocator_type& alloc = allocator_type());	
	 map (const map& x) { //TODO
		 (void) x;
		 throw std::logic_error("Function not yet implemented");
	 }
	 //map& operator= (const map& x);
	 iterator begin() {return _tree.begin();};
	 const_iterator begin() const {return _tree.begin();};
	 iterator end() {return _tree.end();};
	 const_iterator end() const {return _tree.end();};
	 bool empty() {return !_tree._root;}
	 size_type size() {
		 if (empty()) return 0;
		 return _tree._root->size();
	 }
	 size_type max_size() const {return std::numeric_limits<size_type>::max() / sizeof(Avlnode<T>);}
	 //Modifiers
	 pair<iterator,bool> insert (const value_type& val) {
		 if (!empty()) {
			 iterator already_exists = _tree.find(val);
			 if (already_exists != end()) {
				 pair<iterator, bool> retval(already_exists, false);
				 return retval;
			 }
		 }
		 //std::cout << "it was empty or it didn't exist\n";
		 pair<iterator, bool> retval(_tree.insert(val), true);
		 return retval;
	 }
	 mapped_type &operator[] (const key_type &k) {
		 pair<iterator,bool> inserted = insert(pair<key_type, mapped_type>(k,mapped_type()));
		 return (*(inserted.first)).second;
	 }
	 void erase (iterator position) {
		 Avlnode<value_type> *p = reinterpret_cast<Avlnode<value_type> *>(&(*position));
		 p->erase();
		 _tree.reroot();
	 }
	 iterator find (const key_type& k) {
		 return _tree.find(pair<key_type, mapped_type>(k,mapped_type()));
	 }
	 const_iterator find (const key_type& k) const {
		 const pair<key_type, mapped_type> p(k,mapped_type());
		 return const_iterator(_tree.find(p));
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
	 //void erase (iterator first, iterator last); //TODO

	 void swap (map& x) {
		 Avlnode<value_type, compare_key<key_type, mapped_type, Compare> > *s = _tree._root;
		 _tree._root = x._tree._root;
		 x._tree._root = s;
	 }
	//https://stackoverflow.com/questions/14187006/is-calling-destructor-manually-always-a-sign-of-bad-design
	 void clear() {
		 _tree.~Avltree<value_type, compare_key<Key, T, Compare> >();
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
		return _tree.lower_bound(value_type(k, mapped_type()));
	 }
	 iterator lower_bound (const key_type& k) {
		return _tree.lower_bound(value_type(k, mapped_type()));
	 }
	 const_iterator upper_bound (const key_type& k) const {
		return _tree.upper_bound(value_type(k, mapped_type()));
	 }
	 iterator upper_bound (const key_type& k) {
		return _tree.upper_bound(value_type(k, mapped_type()));
	 }
	 pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
		 const_iterator i = find(k);
		 if (i != end()) {
			 return pair<const_iterator,const_iterator>(i, upper_bound(k));
		 }
		 return pair<const_iterator,const_iterator>(upper_bound(k), upper_bound(k));
	 }
	 pair<iterator,iterator> equal_range (const key_type& k) {
		pair<const_iterator,const_iterator> p = const_cast<const map<Key, T, Compare, Alloc> &>(*this).equal_range(k);
		return pair<iterator, iterator>(const_cast<iterator> (p.first), const_cast<iterator> (p.second));
	 }
	 //const_iterator upper_bound (const key_type& k) const; //TODO
}; //map
} //namespace
#endif
