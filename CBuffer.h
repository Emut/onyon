#ifndef CBUFFER_H
#define CBUFFER_H
#include <iostream>
#include "CRect.h"

template <class T>
class CBuffer
{

public:
	CBuffer(int width, int heigth) : m_width(width), m_heigth(heigth)
	{
		m_stride = m_width;
		m_isSelfCreated = true;
		if (width > 0 && heigth > 0)
			m_itsBuffer = new T[width * heigth];
		else
			m_itsBuffer = NULL;
	}
	~CBuffer()
	{
		if (m_isSelfCreated && m_itsBuffer != NULL)
			delete[] m_itsBuffer;
	}

	//copy const. does a shallow copy
	CBuffer(const CBuffer<T> &rhs)
	{
		m_isSelfCreated = false;
		m_heigth = rhs.m_heigth;
		m_width = rhs.m_width;
		m_stride = rhs.m_stride;
		m_itsBuffer = rhs.m_itsBuffer;
	}

	CBuffer(const CBuffer<T> &rhs, CRect<int> borders)
	{
		m_isSelfCreated = false;
		m_heigth = borders.getHeigth();
		m_width = borders.getWidth();
		m_stride = rhs.m_stride;
		m_itsBuffer = rhs.m_itsBuffer +
					  m_stride * borders.getTop() + borders.getLeft();
	}

	const CBuffer<T> operator=(const CBuffer<T> rhs)
	{
		if (m_isSelfCreated && m_itsBuffer != NULL)
			delete[] m_itsBuffer;
		m_itsBuffer = rhs.m_itsBuffer;
		m_stride = rhs.m_stride;
		m_width = rhs.m_width;
		m_heigth = rhs.m_heigth;
		m_isSelfCreated = false;

		return *this;
	}

	T *getBufferPointer()
	{
		return m_itsBuffer;
	}

	void Fill(const T fillThis)
	{
		T *it = m_itsBuffer;
		int strideDiff = m_stride - m_width;
		for (int y = 0; y < m_heigth; ++y)
		{
			for (int x = 0; x < m_width; ++x)
			{
				*it = fillThis;
				++it;
			}
			it += strideDiff;
		}
	}

	T &getElmRef(int x, int y)
	{
		T &retVal = m_itsBuffer[y * m_stride + x];
		return retVal;
	}

	int getWidth()
	{
		return m_width;
	}

	int getHeigth()
	{
		return m_heigth;
	}

	int getStride()
	{
		return m_stride;
	}

	CPoint<int> getSize()
	{
		return CPoint<int>(m_width, m_heigth);
	}

	CRect<int> getAreaRect()
	{
		return CRect<int>(0, 0, m_heigth - 1, m_width - 1);
	}

	void CopyFrom(CBuffer<T> &source)
	{
		int copyWidth = std::min(m_width, source.m_width);
		int copyHeigth = std::min(m_heigth, source.m_heigth);

		T *pdest = m_itsBuffer;
		T *psource = source.m_itsBuffer;
		int destShifter = m_stride;
		int srcShifter = source.m_stride;

		int copySize = sizeof(T)*copyWidth;
		for (int i = 0; i < copyHeigth; ++i)
		{
			memcpy(pdest, psource, copySize);
			pdest += destShifter;
			psource += srcShifter;
		}
	}

private:
	CBuffer(); //disallow defc

	T *m_itsBuffer;
	int m_width;
	int m_heigth;
	int m_stride;
	bool m_isSelfCreated;
};

#endif