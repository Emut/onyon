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
};
