#ifndef CPLOTTER_H
#define CPLOTTER_H

#include <iostream>
#include <vector>
#include "DrawUtils.h"
#include "Colors.h"
#include "CPoint.h"
#include "CRect.h"
#include "CLineData.h"
#include "CLinearIter.h"
#include "CDisplayHandler.h"

class CPlotter
{

public:
	CPlotter(int canvasWidth = 640, int canvasHeigth = 480);

	template <class IterY>
	int Plot(IterY y_begin, IterY y_end)
	{
		CLinearIter<int> dummyIterBegin(1);
		CLinearIter<int> dummyIterEnd(1000);
		return Plot(y_begin, y_end, dummyIterBegin, dummyIterEnd);
	}
	template <class IterY, class IterX>
	int Plot(IterY y_begin, IterY y_end, IterX x_begin, IterX x_end)
	{
		m_lineData.push_back(LineData());
		m_lineData[m_DrawnLineCount].id = m_DrawnLineCount;
		CRGB penColor;
		int moddedCnt = m_DrawnLineCount % 6 + 1;
		penColor.setBlue((moddedCnt & 0x1) * 255);
		penColor.setRed((moddedCnt & 0x2) * 255);
		penColor.setGreen((moddedCnt & 0x4) * 255);
		m_lineData[m_DrawnLineCount].color = penColor;

		IterX x_it = x_begin;
		IterY y_it = y_begin;
		int dataCount = 0;
		float y_min = *y_it;
		float y_max = *y_it;
		float x_min = *x_it;
		float x_max = *x_it;
		while (x_it != x_end && y_it != y_end)
		{ //if x and y data counts do not match, draw until the smallest
			++dataCount;
			if (*y_it < y_min)
			{
				y_min = *y_it;
			}
			if (*y_it > y_max)
			{
				y_max = *y_it;
			}
			if (*x_it > x_max)
			{
				x_max = *x_it;
			}
			if (*x_it < x_min)
			{
				x_min = *x_it;
			}
			++x_it;
			++y_it;
		}
		m_lineData[m_DrawnLineCount].x_max = x_max;
		m_lineData[m_DrawnLineCount].x_min = x_min;
		m_lineData[m_DrawnLineCount].y_max = y_max;
		m_lineData[m_DrawnLineCount].y_min = y_min;
		m_lineData[m_DrawnLineCount].dataCount = dataCount;
		m_lineData[m_DrawnLineCount].xdata = new float[dataCount];
		m_lineData[m_DrawnLineCount].ydata = new float[dataCount];

		x_it = x_begin;
		y_it = y_begin;
		for (int i = 0; i < dataCount; ++i)
		{
			m_lineData[m_DrawnLineCount].xdata[i] = float(*x_it);
			++x_it;
			m_lineData[m_DrawnLineCount].ydata[i] = float(*y_it);
			++y_it;
		}
		++m_DrawnLineCount;
		PlotUpdated();
		return m_lineData[m_DrawnLineCount - 1].id;
	}

	bool ToggleDisplayWindow(bool enable);

	bool SaveAsPgm(const char *fileName);
	bool SaveAsPpm(const char *fileName);

	void setTitle(const char *title);
	void setX_AxisLabel(const char *title);
	void setY_AxisLabel(const char *title);

	bool setLineDataPointMarker(int LineID, LineData::teDataPointMark marker);
	bool setLineColor(int lineID, CRGB color);

private:
	CBuffer<CRGB> m_canvas;
	int m_DrawnLineCount;
	bool m_NeedRedraw;
	char *m_title;
	char *m_xAxisLabel;
	char *m_yAxisLabel;
	CRect<int> m_plotArea;
	CRect<float> m_dataLimits;

	void PlotUpdated();
	void Draw();
	void DrawPlotBorder();
	void DrawTicks();
	LineData *getLineData(int lineID);

	std::vector<LineData> m_lineData;

	bool m_windowEnabled;
	CDisplayHandler *m_itsWindowHandler;
	bool UpdateWindow();
};

#endif