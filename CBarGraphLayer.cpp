#include "CBarGraphLayer.h"
#include <math.h>

void CBarGraphLayer::Draw(CBuffer<CRGB> buf)
{
    m_activeArea = buf.getAreaRect();
    int dataCnt = m_data->size();
    if (dataCnt < 1)
        return;
    float maxData = 0;
    float minData = 0;
    for (int i = 0; i < dataCnt; ++i)
    {
        CSeriesData *data = (*m_data)[i];
        maxData = std::max(data->ydata[0], maxData);
        minData = std::min(data->ydata[0], minData);
    }

    int heigth = m_isVertical ? m_activeArea.getHeigth() : m_activeArea.getWidth();
    int width = !m_isVertical ? m_activeArea.getHeigth() : m_activeArea.getWidth();
    heigth -= 2;
    width -= 2;
    int spacing = 5;

    int barWidth = (width - spacing * (dataCnt - 1)) / dataCnt;
    float heigthPerData = (heigth / ((float)maxData - minData));
    int zeroLocation = m_isVertical ? heigth - heigthPerData * (0 - minData) : heigthPerData * (0 - minData) + 2;

    int shift = 1;
    for (int i = 0; i < dataCnt; ++i)
    {
        CSeriesData *data = (*m_data)[i];
        CRect<int> barBorders;
        //adjust bar width and placing
        if (m_isVertical)
        {
            barBorders.setLeft(shift);
            barBorders.setRight(shift + barWidth);
        }
        else
        {
            barBorders.setTop(shift);
            barBorders.setBottom(shift + barWidth);
        }
        //adjust bar heigth and placement
        if (m_isVertical)
        {
            if (data->ydata[0] > 0)
            {
                barBorders.setBottom(zeroLocation);
                barBorders.setTop(zeroLocation - data->ydata[0] * heigthPerData);
            }
            else
            {
                barBorders.setTop(zeroLocation);
                barBorders.setBottom(zeroLocation - data->ydata[0] * heigthPerData);
            }
        }
        else{
            if (data->ydata[0] > 0)
            {
                barBorders.setLeft(zeroLocation);
                barBorders.setRight(zeroLocation + data->ydata[0] * heigthPerData);
            }
            else
            {
                barBorders.setRight(zeroLocation);
                barBorders.setLeft(zeroLocation + data->ydata[0] * heigthPerData);
            }
        }
        CBuffer<CRGB> drawBuf(buf, barBorders);
        drawBuf.Fill(data->color);
        shift += barWidth + spacing;
    }
}

void CBarGraphLayer::setData(std::vector<CSeriesData *> *data)
{
    m_data = data;
}

CRect<int> CBarGraphLayer::getActiveArea()
{
    return m_activeArea;
}

CBarGraphLayer::CBarGraphLayer(bool isVertical)
{
    m_isVertical = isVertical;
}