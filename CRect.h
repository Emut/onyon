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

	T getTop() { return m_TL.Y(); }
	T getLeft() { return m_TL.X(); }
	T getBottom() { return m_BR.Y(); }
	T getRight() { return m_BR.X(); }

	void setTop(T val) { m_TL.Y() = val; }
	void setBottom(T val) { m_BR.Y() = val; }
	void setLeft(T val) { m_TL.X() = val; }
	void setRight(T val) { m_BR.X() = val; }

	T getWidth() { return m_BR.X() - m_TL.X() + 1; }
	T getHeigth() { return m_BR.Y() - m_TL.Y() + 1; }

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
		if (m_TL.X() > point.X())
			return false;
		if (m_TL.Y() > point.Y())
			return false;
		if (m_BR.X() < point.X())
			return false;
		if (m_BR.Y() < point.Y())
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
		m_TL.ShiftX(shiftBy.X());
		m_BR.ShiftX(shiftBy.X());
		m_TL.ShiftY(shiftBy.Y());
		m_BR.ShiftY(shiftBy.Y());
	}

	CPoint<T> getCenter(){
		return CPoint<T>((m_TL.X()+m_BR.X())/2, (m_TL.Y()+m_BR.Y())/2);
	}
};
