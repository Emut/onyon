#ifndef CPOINT_H
#define CPOINT_H

template<class T>
class CPoint {
public:
	CPoint(T x, T y) : x(x), y(y) {}

	CPoint<T> operator-(CPoint<T> second) {
		return CPoint<T>(x - second.x, y - second.y);
	}

	CPoint<T> operator+(CPoint<T> second) {
		return CPoint<T>(x + second.x, y + second.y);
	}

	CPoint<T> operator/(T denominator) {
		return CPoint<T>(x / denominator, y / denominator);
	}

	bool operator==(const CPoint<T>& rhs){
		return x==rhs.x && y==rhs.y;
	}

	void ShiftX(int shiftBy){
		x += shiftBy;
	}

	void ShiftY(int shiftBy){
		y += shiftBy;
	}

	T x;
	T y;
};

#endif
