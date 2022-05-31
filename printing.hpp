#ifndef PRINTING_HPP
#define PRINTING_HPP

template <class T1, class T2>
std::ostream &operator<<(std::ostream &out, const pair<T1,T2> &p) {
	out << "(" << p.first << ", " << p.second << ")";
	return out;
}

#endif
