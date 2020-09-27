#include "CLegendHandler.h"
#include "DrawUtils.h"

CLegendHandler::CLegendHandler() : m_markerSize(20, 8)
{
    m_colorBackground = CRGB(255, 255, 255);
    m_colorBorder = CRGB(0, 0, 0);
    m_marker = BOX;
}

void CLegendHandler::setData(std::vector<CSeriesData *> *data)
{
    m_data = data;
}

void CLegendHandler::Draw(CBuffer<CRGB> buf)
{
    m_activeArea = buf.getAreaRect();
    if(m_data->size() == 0)
        return;
    CPoint<int> legendSize(0, 0);

    for (int i = 0; i < m_data->size(); ++i)
    {
        CSeriesData *data = m_data->at(i);
        CPoint<int> size = DrawUtils<CRGB>::getStringSize(data->name);
        legendSize.ShiftY(size.y + 1);
        legendSize.x = legendSize.x < size.x ? size.x : legendSize.x;
    }
    //widen by 4 to fit text
    legendSize.ShiftX(4);

    if (m_marker != NONE)
    {
        legendSize.ShiftX(m_markerSize.x + 4);
    }

    CRect<int> legendArea;

    CPoint<int> legendTL(buf.getWidth() - legendSize.x - 2, 1);
    legendArea.setTop(legendTL.y);
    legendArea.setLeft(legendTL.x);
    legendArea.setRight(legendTL.x + legendSize.x);
    legendArea.setBottom(legendTL.y + legendSize.y);

    CBuffer<CRGB> canvasLegend(buf, legendArea);
    if(m_colorBackground.isGrayScale())
        canvasLegend.FillWithByte(m_colorBackground.getBlue());
    else
        canvasLegend.Fill(m_colorBackground);
    DrawUtils<CRGB>::DrawRectangle(canvasLegend, CRGB(0, 0, 0), canvasLegend.getAreaRect());

    CPoint<int> writePos(1, 1);
    if (m_marker != NONE)
    {
        writePos.ShiftX(m_markerSize.x + 4);
    }
    for (int i = 0; i < m_data->size(); ++i)
    {
        CSeriesData *data = m_data->at(i);
        CPoint<int> textSize = DrawUtils<CRGB>::getStringSize(data->name);
        CPoint<int> markerPos = writePos;
        markerPos.ShiftX(-m_markerSize.x - 2);
        markerPos.ShiftY((textSize.y - m_markerSize.y)/2);
        CPoint<int> markerBR = markerPos;
        markerBR = markerBR + m_markerSize;
        CRect<int> boxMarker(markerPos, markerBR);
        CBuffer<CRGB> canvasMarker(canvasLegend, boxMarker);
        DrawLegendMarker(canvasMarker, data->color);
        DrawUtils<CRGB>::DrawString(canvasLegend,
                                    data->color,
                                    writePos,
                                    data->name);
        writePos.ShiftY(textSize.y + 1);
    }
}

CRect<int> CLegendHandler::getActiveArea()
{
    return m_activeArea;
}

void CLegendHandler::DrawLegendMarker(CBuffer<CRGB> &buf, CRGB color)
{
    switch (m_marker)
    {
    case BOX:
    {
        buf.Fill(color);
    }
    break;
    case LINE:
        break;

    default:
        break;
    }
}