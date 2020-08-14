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

	static void DrawLine(CBuffer<T> &buf, const T fill, CPoint<float> begin, CPoint<float> end)
	{
		DrawLine(buf, fill, begin.x, begin.y, end.x, end.y);
	}
	static void DrawLineAngle(CBuffer<T> &buf, const T fill, int x, int y, int length, float radAngle)
	{
		int endX = x + ROUND(length * cos(radAngle));
		int endY = y + ROUND(length * sin(radAngle));

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
		DrawCircle(buf, fill, center.x, center.y, radius);
	}
	static void DrawString(CBuffer<T> &buf, const T fill, CPoint<int> pos, const char *string)
	{
		IFont *itsFont = CFontFactory::getFont("7_12_Serif", 12);
		while (*string != 0)
		{
			tsLetterGlyph *currentLetter = itsFont->getLetter(*string);
			for (int i = 0; i < currentLetter->corePxCnt; ++i)
			{
				buf.getElmRef(pos.x + currentLetter->corePxs[i].X, pos.y + currentLetter->corePxs[i].Y) = fill;
			}
			pos.x += currentLetter->width + 1;
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
			size.x += currentLetter->width + 1; //include the 1px gap between chars
			if (size.y < currentLetter->heigth)
				size.y = currentLetter->heigth;
			++string;
		}
		--size.x; //numOfGaps is one less than letters
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
				buf.getElmRef(pos.x + currentLetter->corePxs[i].Y, pos.y - currentLetter->corePxs[i].X) = fill;
			}
			pos.y -= currentLetter->width + 1;
			++string;
		}
	}

	static void DrawRectangle(CBuffer<T> &buf, const T fill, CPoint<int> TopLeft, CPoint<int> BottomRight)
	{
		DrawUtils<T>::DrawLine(buf, fill, TopLeft.x, TopLeft.y, TopLeft.x, BottomRight.y);
		DrawUtils<T>::DrawLine(buf, fill, TopLeft.x, TopLeft.y, BottomRight.x, TopLeft.y);
		DrawUtils<T>::DrawLine(buf, fill, TopLeft.x, BottomRight.y, BottomRight.x, BottomRight.y);
		DrawUtils<T>::DrawLine(buf, fill, BottomRight.x, TopLeft.y, BottomRight.x, BottomRight.y);
	}

	static void DrawRectangle(CBuffer<T> &buf, const T fill, CRect<int> rect)
	{
		DrawRectangle(buf, fill, rect.getTopLeft(), rect.getBottomRight());
	}

	static void DrawArc(CBuffer<T> &buf, const T fill, CPoint<int> center, int radius, float startAngle, float endAngle)
	{
		CPoint<int> pntStart(center.x + ROUND(radius * cos(startAngle)), center.y + ROUND(radius * sin(startAngle)));
		CPoint<int> pntEnd(center.x + ROUND(radius * cos(endAngle)), center.y + ROUND(radius * sin(endAngle)));
		float midAngle = startAngle + endAngle;
		midAngle /= 2;
		CPoint<int> pntMid(center.x + ROUND(radius * cos(midAngle)), center.y + ROUND(radius * sin(midAngle)));
		if (pntMid == pntStart || pntMid == pntEnd)
			return;
		buf.getElmRef(pntMid.x, pntMid.y) = fill;
		DrawArc(buf, fill, center, radius, startAngle, midAngle);
		DrawArc(buf, fill, center, radius, midAngle, endAngle);
	}

	static void DrawPie(CBuffer<T> &buf, const T fill, CPoint<int> center, int radius, float startAngle, float endAngle)
	{
		DrawLineAngle(buf, fill, center.x, center.y, radius, startAngle);
		DrawLineAngle(buf, fill, center.x, center.y, radius, endAngle);
		DrawArc(buf, fill, center, radius, startAngle, endAngle);
	}

	static void Fill(CBuffer<T> &buf, const T fill, CPoint<int> start)
	{
		if (buf.getElmRef(start.x, start.y) == fill)
			return;
		buf.getElmRef(start.x, start.y) = fill;

		start.ShiftX(1);
		if (!(buf.getElmRef(start.x, start.y) == fill))
			Fill(buf, fill, start);

		start.ShiftX(-2);
		if (!(buf.getElmRef(start.x, start.y) == fill))
			Fill(buf, fill, start);

		start.ShiftX(1);
		start.ShiftY(1);
		if (!(buf.getElmRef(start.x, start.y) == fill))
			Fill(buf, fill, start);

		start.ShiftY(-2);
		if (!(buf.getElmRef(start.x, start.y) == fill))
			Fill(buf, fill, start);
	}
};

#endif