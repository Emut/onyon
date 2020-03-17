#ifndef CPOINT_H
#define CPOINT_H

template<class T>
class CPoint {
public:
	CPoint(T x, T y) : m_x(x), m_y(y) {}

	T& X() { return m_x; }
	T& Y(){return m_y;}
	CPoint<T> operator-(CPoint<T> second) {
		return CPoint<T>(X() - second.X(), Y() - second.Y());
	}

private:
	T m_x;
	T m_y;
};

#endif
