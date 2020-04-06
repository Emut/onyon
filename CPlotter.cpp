#include "CPlotter.h"
#include "CImageSaver.h"
#include <string.h>
#include "CLinearIter.h"

CPlotter::CPlotter(int canvasWidth, int canvasHeigth) : m_canvas(canvasWidth, canvasHeigth), m_plotArea(10, 10, canvasHeigth - 10, canvasWidth - 10)
{
	m_canvas.Fill(CRGB(255, 255, 255));
	m_DrawnLineCount = 0;
	m_title = NULL;
	m_xAxisLabel = NULL;
	m_yAxisLabel = NULL;
	m_NeedRedraw = false;
}

bool CPlotter::SaveAsPgm(const char *fileName)
{
	if (m_NeedRedraw)
	{
		m_NeedRedraw = false;
		Draw();
	}
	return CImageSaver::SaveAsPgm(m_canvas, fileName);
}

bool CPlotter::SaveAsPpm(const char *fileName)
{
	if (m_NeedRedraw)
	{
		m_NeedRedraw = false;
		Draw();
	}
	return CImageSaver::SaveAsPpm(m_canvas, fileName);
}

void CPlotter::setTitle(const char *title)
{
	if (m_title != NULL)
		delete[] m_title;
	m_title = new char[strlen(title)];
	strcpy(m_title, title);
	m_NeedRedraw = true;
}
void CPlotter::setX_AxisLabel(const char *label)
{
	if (m_xAxisLabel != NULL)
		delete[] m_xAxisLabel;
	m_xAxisLabel = new char[strlen(label)];
	strcpy(m_xAxisLabel, label);
	m_NeedRedraw = true;
}
void CPlotter::setY_AxisLabel(const char *label)
{
	if (m_yAxisLabel != NULL)
		delete[] m_yAxisLabel;
	m_yAxisLabel = new char[strlen(label)];
	strcpy(m_yAxisLabel, label);
	m_NeedRedraw = true;
}

void CPlotter::DrawPlotBorder()
{
	DrawUtils<CRGB>::DrawRectangle(m_canvas, CRGB(0, 0, 0), m_plotArea.getTopLeft(), m_plotArea.getBottomRight());
}

void CPlotter::Draw()
{
	printf("Draw\n");
	m_canvas.Fill(CRGB(255, 255, 255)); //clear the canvas
	if (m_title != NULL)
	{
		CPoint<int> size = DrawUtils<CRGB>::getStringSize(m_title);
		CPoint<int> pos((m_canvas.getWidth() - size.X()) / 2, 5);
		DrawUtils<CRGB>::DrawString(m_canvas, CRGB(0, 0, 0), pos, m_title);
		m_plotArea.setTop(20);
	}
	if (m_xAxisLabel != NULL)
	{
		CPoint<int> size = DrawUtils<CRGB>::getStringSize(m_xAxisLabel);
		CPoint<int> pos((m_canvas.getWidth() - size.X()) / 2, m_canvas.getHeigth() - 15);
		DrawUtils<CRGB>::DrawString(m_canvas, CRGB(0, 0, 0), pos, m_xAxisLabel);
		m_plotArea.setBottom(m_canvas.getHeigth() - 20);
	}
	if (m_yAxisLabel != NULL)
	{
		CPoint<int> size = DrawUtils<CRGB>::getStringSize(m_yAxisLabel);
		CPoint<int> pos(5, (m_canvas.getHeigth() + size.X()) / 2);
		DrawUtils<CRGB>::DrawStringRotatedLeft(m_canvas, CRGB(0, 0, 0), pos, m_yAxisLabel);
		m_plotArea.setLeft(20);
	}

	DrawPlotBorder();

	//get the extreme values on the lines

	if (m_DrawnLineCount <= 0)
		return;

	m_dataLimits.setTop(m_lineData[0].y_min);
	m_dataLimits.setBottom(m_lineData[0].y_max);
	m_dataLimits.setLeft(m_lineData[0].x_min);
	m_dataLimits.setRight(m_lineData[0].x_max);
	for (int i = 1; i < m_DrawnLineCount; ++i)
	{
		if (m_lineData[i].x_min < m_dataLimits.getLeft())
			m_dataLimits.setLeft(m_lineData[i].x_min);
		if (m_lineData[i].y_min < m_dataLimits.getTop())
			m_dataLimits.setTop(m_lineData[i].y_min);
		if (m_lineData[i].x_max > m_dataLimits.getRight())
			m_dataLimits.setRight(m_lineData[i].x_max);
		if (m_lineData[i].y_max > m_dataLimits.getBottom())
			m_dataLimits.setBottom(m_lineData[i].y_max);
	}

	for (int i = 0; i < m_DrawnLineCount; ++i)
	{
		float y_prev = m_lineData[i].ydata[0];
		float x_prev = m_lineData[i].xdata[0];
		for (int j = 0; j < m_lineData[i].dataCount; ++j)
		{
			float x = m_lineData[i].xdata[j];
			float y = m_lineData[i].ydata[j];
			x = (x - m_dataLimits.getLeft()) / m_dataLimits.getWidth() * (m_plotArea.getBottomRight() - m_plotArea.getTopLeft()).X() + m_plotArea.getTopLeft().X();
			y = (y - m_dataLimits.getTop()) / m_dataLimits.getHeigth() * (m_plotArea.getBottomRight() - m_plotArea.getTopLeft()).Y() + m_plotArea.getTopLeft().Y();
			if (j != 0)
			{
				DrawUtils<CRGB>::DrawLine(m_canvas, m_lineData[i].color, x_prev, y_prev, x, y);
			}
			if (m_lineData[i].dataPointMarker == LineData::DPM_CIRCLE)
				DrawUtils<CRGB>::DrawCircle(m_canvas, m_lineData[i].color, x, y, 3);

			y_prev = y;
			x_prev = x;
		}
	}
	DrawTicks();
}

void CPlotter::DrawTicks()
{
	return;
	//stubbed for now. Work will continue on a branch
	char nums[10];
	sprintf(nums, "%04.1f", m_dataLimits.getRight());
	DrawUtils<CRGB>::DrawString(m_canvas, CRGB(0, 0, 0), m_plotArea.getBottomRight() - CPoint<int>(30, 0), nums);

	sprintf(nums, "%04.1f", m_dataLimits.getLeft());
	DrawUtils<CRGB>::DrawString(m_canvas, CRGB(0, 0, 0), CPoint<int>(m_plotArea.getLeft(), m_plotArea.getBottom()), nums);
}

LineData *CPlotter::getLineData(int lineID)
{
	for (size_t i = 0; i < m_lineData.size(); ++i)
	{
		if (m_lineData[i].id == lineID)
			return &m_lineData[i];
	}
	return NULL;
}

bool CPlotter::setLineDataPointMarker(int lineID, LineData::teDataPointMark marker)
{
	LineData* pLine = getLineData(lineID);
	if(pLine == NULL)
		return false;
	if(pLine->dataPointMarker == marker)
		return true;
	pLine->dataPointMarker = marker;
	m_NeedRedraw = true;
	return true;
}
bool CPlotter::setLineColor(int lineID, CRGB color)
{
	LineData* pLine = getLineData(lineID);
	if(pLine == NULL)
		return false;
	if(color == pLine->color)
		return true;	//no need to change color
	pLine->color = color;
	m_NeedRedraw = true;
	return true;
}