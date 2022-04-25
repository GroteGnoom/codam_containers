#include "map.hpp"
#include <iostream>

using namespace ft;

template <typename T>
void print_avl(ft::Avlnode<T> *a , int spaces ) {
	if (!a) return;
	print_avl(a->_right, spaces + 5 );
	for (int i = 1; i <= spaces; ++i ) {
		std::cout << " ";
	}
	std::cout << a->_elem << "\n";
	print_avl( a->_left, spaces + 5 );
}

int main() {
	Avltree<int> a;

	a.insert(3);
	a.insert(7);
	a.insert(5);
	a.insert(9);
	a.insert(1);

	print_avl(a._root, 0);
}

