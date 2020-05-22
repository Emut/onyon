#ifndef DRAWUTILS_H
#define DRAWUTILS_H

#include "CBuffer.h"
#include "CFont.h"
#include "CFontFactory.h"
#include <algorithm>
#include "CPoint.h"
#include <math.h>
#define ROUND(X) int(X < 0 ? ceil(X - 0.5) : floor(X + 0.5))

template <class T>
class DrawUtils
{
public:
	static void DrawLine(CBuffer<T> &buf, const T fill, int x1, int y1, int x2, int y2)
	{

		if (x1 == x2)
		{
			int lowerY = std::min(y1, y2);
			int upperY = std::max(y1, y2);
			for (int i = lowerY; i <= upperY; ++i)
			{
				buf.getElmRef(x1, i) = fill;
			}
			return;
		}

		float slope = (float(y1) - y2) / (x1 - x2);

		if (std::abs(slope) <= 1)
		{
			int lowerX = std::min(x1, x2);
			int upperX = std::max(x1, x2);
			for (int i = lowerX; i <= upperX; ++i)
			{
				int y = ROUND(y1 + (i - x1) * slope);
				buf.getElmRef(i, y) = fill;
			}
		}
		else
		{
			float invSlope = 1 / slope;
			int lowerY = std::min(y1, y2);
			int upperY = std::max(y1, y2);
			for (int i = lowerY; i <= upperY; ++i)
			{
				int x = ROUND(x1 + (i - y1) * invSlope);
				buf.getElmRef(x, i) = fill;
			}
		}
	}

	static void DrawLine(CBuffer<T> &buf, const T fill, int x, int y, int length, float radAngle)
	{
		int endX = x +  ROUND(length*cos(radAngle));
		int endY = y + ROUND(length*sin(radAngle));

		DrawLine(buf, fill, x, y, endX, endY);
	}

	static void DrawCircle(CBuffer<T> &buf, const T fill, int x, int y, int radius)
	{
		int radsq = radius * radius;
		for (int i = 0; i < radius; ++i)
		{
			int offset = ROUND(sqrt(radsq - i * i));
			buf.getElmRef(x + i, y + offset) = fill;
			buf.getElmRef(x + i, y - offset) = fill;
			buf.getElmRef(x - i, y + offset) = fill;
			buf.getElmRef(x - i, y - offset) = fill;
			buf.getElmRef(x + offset, y + i) = fill;
			buf.getElmRef(x + offset, y - i) = fill;
			buf.getElmRef(x - offset, y + i) = fill;
			buf.getElmRef(x - offset, y - i) = fill;
		}
	}

	static void DrawCircle(CBuffer<T> &buf, const T fill, CPoint<int> center, int radius)
	{
		DrawCircle(buf, fill, center.X(), center.Y(), radius);
	}
	static void DrawString(CBuffer<T> &buf, const T fill, CPoint<int> pos, const char *string)
	{
		IFont *itsFont = CFontFactory::getFont("7_12_Serif", 12);
		while (*string != 0)
		{
			tsLetterGlyph *currentLetter = itsFont->getLetter(*string);
			for (int i = 0; i < currentLetter->corePxCnt; ++i)
			{
				buf.getElmRef(pos.X() + currentLetter->corePxs[i].X, pos.Y() + currentLetter->corePxs[i].Y) = fill;
			}
			pos.X() += currentLetter->width + 1;
			++string;
		}
	}

	static CPoint<int> getStringSize(const char *string)
	{
		IFont *itsFont = CFontFactory::getFont("7_12_Serif", 12);
		CPoint<int> size(0, 0);
		while (*string != 0)
		{
			tsLetterGlyph *currentLetter = itsFont->getLetter(*string);
			size.X() += currentLetter->width + 1; //include the 1px gap between chars
			if (size.Y() < currentLetter->heigth)
				size.Y() = currentLetter->heigth;
			++string;
		}
		--size.X(); //numOfGaps is one less than letters
		return size;
	}
	/*
	static void DrawStringVertical(CBuffer<T>& buf, const T fill, CPoint<int> pos, char* string) {
		IFont* itsFont = CFontFactory::getFont("7_12_Serif", 12);
		while (*string != 0) {
			tsLetterGlyph* currentLetter = itsFont->getLetter(*string);
			for (int i = 0; i < currentLetter->corePxCnt; ++i) {
				buf.getElmRef(x + currentLetter->corePxs[i].X, y + currentLetter->corePxs[i].Y) = fill;
			}
			y += currentLetter->heigth + 1;
			++string;
		}
	}
*/
	static void DrawStringRotatedLeft(CBuffer<T> &buf, const T fill, CPoint<int> pos, char *string)
	{
		IFont *itsFont = CFontFactory::getFont("7_12_Serif", 12);
		while (*string != 0)
		{
			tsLetterGlyph *currentLetter = itsFont->getLetter(*string);
			for (int i = 0; i < currentLetter->corePxCnt; ++i)
			{
				buf.getElmRef(pos.X() + currentLetter->corePxs[i].Y, pos.Y() - currentLetter->corePxs[i].X) = fill;
			}
			pos.Y() -= currentLetter->width + 1;
			++string;
		}
	}

	static void DrawRectangle(CBuffer<T> &buf, const T fill, CPoint<int> TopLeft, CPoint<int> BottomRight)
	{
		DrawUtils<T>::DrawLine(buf, fill, TopLeft.X(), TopLeft.Y(), TopLeft.X(), BottomRight.Y());
		DrawUtils<T>::DrawLine(buf, fill, TopLeft.X(), TopLeft.Y(), BottomRight.X(), TopLeft.Y());
		DrawUtils<T>::DrawLine(buf, fill, TopLeft.X(), BottomRight.Y(), BottomRight.X(), BottomRight.Y());
		DrawUtils<T>::DrawLine(buf, fill, BottomRight.X(), TopLeft.Y(), BottomRight.X(), BottomRight.Y());
	}
};

#endif