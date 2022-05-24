#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {

template <class T>
struct is_integral{
	static const bool value = false;
};

/*
template <class T>
struct nq {
	typedef T type;
};

template <class T>
struct nq<const T> {
	typedef T type;
};

template <class T>
struct nq<volatile const T> {
	typedef T type;
};

template <class T>
struct nq<volatile T> {
	typedef T type;
};
*/

#define all_int \
	is_int(bool);\
	is_int(char);\
	is_int(signed char);\
	is_int(unsigned char);\
	is_int(wchar_t);\
	is_int(short);\
	is_int(unsigned short);\
	is_int(int);\
	is_int(unsigned int);\
	is_int(long);\
	is_int(unsigned long);\
	is_int(long long);\

//the compiler tells me:
//template specialization requires 'template<>'
#define is_int(_type_) template <> struct is_integral<_type_>{ static const bool value = true; };
	all_int
#undef is_int
#define is_int(_type_) template <> struct is_integral<const _type_>{ static const bool value = true; };
	all_int
#undef is_int
#define is_int(_type_) template <> struct is_integral<volatile const _type_>{ static const bool value = true; };
	all_int
#undef is_int
#define is_int(_type_) template <> struct is_integral<volatile _type_>{ static const bool value = true; };
	all_int
#undef is_int


}

#endif
