#include "CLegendHandler.h"
#include "DrawUtils.h"

CLegendHandler::CLegendHandler(): m_markerSize(20,12){
    m_colorBackground = CRGB(255,255,255);
    m_colorBorder = CRGB(0,0,0);
    m_marker = BOX;
}

void CLegendHandler::setData(std::vector<CSeriesData *> *data)
{
    m_data = data;
}

void CLegendHandler::Draw(CBuffer<CRGB> buf)
{
    CPoint<int> legendSize(0,0);

    for (int i = 0; i < m_data->size(); ++i)
    {
        CSeriesData *data = m_data->at(i);
        CPoint<int> size = DrawUtils<CRGB>::getStringSize(data->name);
        legendSize.ShiftY(size.Y() + 1);
        legendSize.X() = legendSize.X() < size.X() ? size.X() : legendSize.X(); 
    }
        //widen by 2 to fit text
        legendSize.ShiftX(2);

    if(m_marker != NONE){
        legendSize.ShiftX(m_markerSize.X());
    }

    CRect<int> legendArea;
    
    CPoint<int> legendTL(buf.getWidth() - legendSize.X() - 2, 1);
    legendArea.setTop(legendTL.Y());
    legendArea.setLeft(legendTL.X());
    legendArea.setRight(legendTL.X() + legendSize.X());
    legendArea.setBottom(legendTL.Y() + legendSize.Y());

    CBuffer<CRGB> canvasLegend(buf, legendArea);
    canvasLegend.Fill(m_colorBackground);
    DrawUtils<CRGB>::DrawRectangle(canvasLegend,CRGB(0,0,0), canvasLegend.getAreaRect());

    CPoint<int> writePos(1,1);
    if(m_marker != NONE){
        writePos.ShiftX(m_markerSize.X());
    }
    for (int i = 0; i < m_data->size(); ++i)
    {
        CSeriesData *data = m_data->at(i);
        DrawUtils<CRGB>::DrawString(canvasLegend,
                                    data->color,
                                    writePos,
                                    data->name);
    writePos.ShiftY(DrawUtils<CRGB>::getStringSize(data->name).Y() + 1);
    }
    m_activeArea = buf.getAreaRect();
}

CRect<int> CLegendHandler::getActiveArea()
{
    return m_activeArea;
}