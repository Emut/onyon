#ifndef CPLOTTER_H
#define CPLOTTER_H

#include <iostream>
#include <vector>
#include "DrawUtils.h"
#include "Colors.h"
#include "CPoint.h"
#include "CRect.h"
using namespace std;

class CPlotter{
	//class to be used as a simply counting iterator
	template<class T>
	class CLinearIter{
		T m_i;
	public:
		CLinearIter(T i): m_i(i){}
		void operator++(){
			++m_i;
		}
		CLinearIter<T>& operator++(int){
			++m_i;
			return *this;
		}
		bool operator!=(const CLinearIter<T>& comp){
			return m_i != comp.m_i;
		}
		T& operator*(){
			return m_i;
		}
		CLinearIter<T>& operator=(const CLinearIter<T>& copyFrom){
			m_i = copyFrom.m_i;
			return *this;
		}
		CLinearIter(const CLinearIter<T>& copyFrom){
			m_i = copyFrom.m_i;
		}
	};

public:
	CPlotter(int canvasWidth = 640, int canvasHeigth = 480);

	template<class IterY>
	void Plot(IterY y_begin, IterY y_end){
		CLinearIter<int> dummyIterBegin(1);
		CLinearIter<int> dummyIterEnd(1000);
		Plot(y_begin, y_end, dummyIterBegin, dummyIterEnd);
	}
	template<class IterY, class IterX>
	void Plot(IterY y_begin, IterY y_end, IterX x_begin, IterX x_end){
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
		while (x_it != x_end && y_it != y_end) {	//if x and y data counts do not match, draw until the smallest
			++dataCount;
			if (*y_it < y_min) { y_min = *y_it; }
			if (*y_it > y_max) { y_max = *y_it; }
			if (*x_it > x_max) { x_max = *x_it; }
			if (*x_it < x_min) { x_min = *x_it; }
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
		for (int i = 0; i < dataCount; ++i) {
			m_lineData[m_DrawnLineCount].xdata[i] = float(*x_it);
			++x_it;
			m_lineData[m_DrawnLineCount].ydata[i] = float(*y_it);
			++y_it;
		}
		++m_DrawnLineCount;
		Draw();
	}

	bool SaveAsPgm(const char* fileName);
	bool SaveAsPpm(const char* fileName);

	void setTitle(const char* title);
	void setX_AxisLabel(const char* title);
	void setY_AxisLabel(const char* title);

private:
	//int m_canvasWidth;
	//int m_canvasHeigth;
	CBuffer<CRGB> m_canvas;
	int m_DrawnLineCount;
	char* m_title;
	char* m_xAxisLabel;
	char* m_yAxisLabel;
	//CPoint<int> m_plotAreaTL;
	//CPoint<int> m_plotAreaBR;
	CRect<int> m_plotArea;
	CRect<float> m_dataLimits;

	void Draw();
	void DrawPlotBorder();
	void DrawTicks();

	struct LineData{
		int id;
		float y_min, y_max, x_min, x_max;
		CRGB color;
		int dataCount;
		float *ydata, *xdata;
	};
	vector<LineData> m_lineData;
};


#endif