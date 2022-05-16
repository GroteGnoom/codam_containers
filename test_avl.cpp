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
	std::cout << a->_elem << "," << a->get_height() << "," << a->get_balance() << "\n";
	print_avl( a->_left, spaces + 5 );
}

int main() {
	Avltree<int> a;

	std::cout << "Insert 3:\n";
	a.insert(3);
	print_avl(a._root, 0);
	std::cout << "Insert 7:\n";
	a.insert(7);
	print_avl(a._root, 0);
	std::cout << "left rotate 3:\n";
	a._root->left_rotate();
	a._root = a._root->root();
	print_avl(a._root, 0);
	std::cout << "right rotate 3:\n";
	a._root->right_rotate();
	a._root = a._root->root();
	print_avl(a._root, 0);

	std::cout << "Insert 5:\n";
	a.insert(5);
	print_avl(a._root, 0);

	/*
	std::cout << "right rotate 7:\n";
	a._root->_right->right_rotate();
	a._root = a._root->root();
	print_avl(a._root, 0);
	std::cout << "left rotate 3:\n";
	a._root->left_rotate();
	a._root = a._root->root();
	print_avl(a._root, 0);
	*/

	std::cout << "Insert 9:\n";
	a.insert(9);
	print_avl(a._root, 0);
	std::cout << "Insert 1:\n";
	a.insert(1);
	print_avl(a._root, 0);


	std::cout << "Remove right children:\n";
	a._root->_right->del_children();
	print_avl(a._root, 0);

	std::cout << "Remove root children:\n";
	a._root->del_children();
	print_avl(a._root, 0);

	std::cout << "Insert 4 more nodes, check if it's balanced:\n";
	a.insert(10);
	a.insert(11);
	a.insert(12);
	a.insert(13);

	print_avl(a._root, 0);
	//std::cout << "Erase root:\n";
	//a._root->erase();
	//print_avl(a._root, 0);
	std::cout << "Erase 12:\n";
	reinterpret_cast<Avlnode<int>*>(a.find(12))->erase();
	print_avl(a._root, 0);
}

