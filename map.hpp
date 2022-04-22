
namespace ft {

template <class T1, class T2>
struct pair;

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
};


}
