#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
template <class T1, class T2>
struct pair{
	public:
	//Member types
	typedef T1 first_type;
	typedef T2 second_type;

	//Member variables
	T1 first;
	T2 second;

	//constructors
	//default
	pair() : first(), second() {};

	//copy
	template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

	//initialization
	pair (const first_type& a, const second_type& b) : first(a), second(b) {}

	//copy assignment
	pair &operator=(const pair<T1, T2> &p) {
		first = p.first;
		second= p.second;
		return *this;
	}

	//Destructor
	~pair() {};

	//implicit conversion
	operator pair< const T1, const T2> () const
	{
		return (pair< const T1, const T2>());
	}
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 t1, T2 t2) {return pair<T1, T2>(t1, t2);}

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

}
#endif
