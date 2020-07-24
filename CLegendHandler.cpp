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
        legendSize.ShiftY(size.Y() + 1);
        legendSize.X() = legendSize.X() < size.X() ? size.X() : legendSize.X();
    }
    //widen by 4 to fit text
    legendSize.ShiftX(4);

    if (m_marker != NONE)
    {
        legendSize.ShiftX(m_markerSize.X() + 4);
    }

    CRect<int> legendArea;

    CPoint<int> legendTL(buf.getWidth() - legendSize.X() - 2, 1);
    legendArea.setTop(legendTL.Y());
    legendArea.setLeft(legendTL.X());
    legendArea.setRight(legendTL.X() + legendSize.X());
    legendArea.setBottom(legendTL.Y() + legendSize.Y());

    CBuffer<CRGB> canvasLegend(buf, legendArea);
    canvasLegend.Fill(m_colorBackground);
    DrawUtils<CRGB>::DrawRectangle(canvasLegend, CRGB(0, 0, 0), canvasLegend.getAreaRect());

    CPoint<int> writePos(1, 1);
    if (m_marker != NONE)
    {
        writePos.ShiftX(m_markerSize.X() + 4);
    }
    for (int i = 0; i < m_data->size(); ++i)
    {
        CSeriesData *data = m_data->at(i);
        CPoint<int> textSize = DrawUtils<CRGB>::getStringSize(data->name);
        CPoint<int> markerPos = writePos;
        markerPos.ShiftX(-m_markerSize.X() - 2);
        markerPos.ShiftY((textSize.Y() - m_markerSize.Y())/2);
        CPoint<int> markerBR = markerPos;
        markerBR = markerBR + m_markerSize;
        CRect<int> boxMarker(markerPos, markerBR);
        CBuffer<CRGB> canvasMarker(canvasLegend, boxMarker);
        DrawLegendMarker(canvasMarker, data->color);
        DrawUtils<CRGB>::DrawString(canvasLegend,
                                    data->color,
                                    writePos,
                                    data->name);
        writePos.ShiftY(textSize.Y() + 1);
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