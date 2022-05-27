#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {

//https://www.cplusplus.com/reference/iterator/iterator/
//This base class only provides some member types, which in fact are not required to be present in any iterator type (iterator types have no specific member requirements), but they might be useful, since they define the members needed for the default iterator_traits class template to generate the appropriate instantiation automatically (and such instantiation is required to be valid for all iterator types).
template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct general_iterator {
	public:
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
};
}

#endif
