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

	CPoint<T> operator+(CPoint<T> second) {
		return CPoint<T>(X() + second.X(), Y() + second.Y());
	}

	CPoint<T> operator/(T denominator) {
		return CPoint<T>(X() / denominator, Y() / denominator);
	}

	bool operator==(const CPoint<T>& rhs){
		return m_x==rhs.m_x && m_y==rhs.m_y;
	}

	void ShiftX(int shiftBy){
		m_x += shiftBy;
	}

	void ShiftY(int shiftBy){
		m_y += shiftBy;
	}

private:
	T m_x;
	T m_y;
};

#endif
