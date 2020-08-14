#pragma once

#include "CPoint.h"

template <class T>
class CRect
{
private:
	CPoint<T> m_TL;
	CPoint<T> m_BR;

public:
	CRect(T top, T left, T bottom, T right) : m_TL(left, top), m_BR(right, bottom) {}
	CRect(CPoint<T> topLeft, CPoint<T> bottomRight) : m_TL(topLeft), m_BR(bottomRight) {}
	CRect() : m_TL(0, 0), m_BR(0, 0) {}

	T getTop() { return m_TL.y; }
	T getLeft() { return m_TL.x; }
	T getBottom() { return m_BR.y; }
	T getRight() { return m_BR.x; }

	void setTop(T val) { m_TL.y = val; }
	void setBottom(T val) { m_BR.y = val; }
	void setLeft(T val) { m_TL.x = val; }
	void setRight(T val) { m_BR.x = val; }

	T getWidth() { return m_BR.x - m_TL.x + 1; }
	T getHeigth() { return m_BR.y - m_TL.y + 1; }

	CPoint<T> getBottomRight() { return m_BR; }
	CPoint<T> getTopLeft() { return m_TL; }

	CRect<T> operator+=(CPoint<T> rhs)
	{
		m_TL = m_TL + rhs;
		m_BR = m_BR + rhs;
		return *this;
	}

	bool IsIn(CPoint<T> point)
	{
		if (m_TL.x > point.x)
			return false;
		if (m_TL.y > point.y)
			return false;
		if (m_BR.x < point.x)
			return false;
		if (m_BR.y < point.y)
			return false;

		return true;
	}

	void ShiftTop(int shiftBy){
		m_TL.ShiftY(shiftBy);
	}

	void ShiftLeft(int shiftBy){
		m_TL.ShiftX(shiftBy);
	}

	void ShiftBottom(int shiftBy){
		m_BR.ShiftY(shiftBy);
	}

	void ShiftRight(int shiftBy){
		m_BR.ShiftX(shiftBy);
	}

	void ShiftBy(CPoint<T> shiftBy){
		m_TL.ShiftX(shiftBy.x);
		m_BR.ShiftX(shiftBy.x);
		m_TL.ShiftY(shiftBy.y);
		m_BR.ShiftY(shiftBy.y);
	}

	CPoint<T> getCenter(){
		return CPoint<T>((m_TL.x+m_BR.x)/2, (m_TL.y+m_BR.y)/2);
	}
};
