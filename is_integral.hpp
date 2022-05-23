#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {

template <class T>
struct is_integral{
	static const int value = false;
};

//the compiler tells me:
//template specialization requires 'template<>'
#define is_int(type) template <> struct is_integral<type>{ static const int value = true; };
	is_int(bool);
	is_int(char);
	is_int(signed char);
	is_int(unsigned char);
	is_int(wchar_t);
	is_int(short);
	is_int(unsigned short);
	is_int(int);
	is_int(unsigned int);
	is_int(long);
	is_int(unsigned long);
	is_int(long long);
#undef is_int


}

#endif
