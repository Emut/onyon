#include "CPieChartLayer.h"
#include "DrawUtils.h"

void CPieChartLayer::setData(std::vector<CSeriesData *> *data)
{
    m_data = data;
}

CRect<int> CPieChartLayer::getActiveArea()
{
    return m_activeArea;
}

void CPieChartLayer::Draw(CBuffer<CRGB> buf)
{
    m_activeArea = buf.getAreaRect();
    // buf.Fill(CRGB(255, 0, 0));

    CPoint<int> center = m_activeArea.getCenter();
    int radius = std::min(m_activeArea.getHeigth(), m_activeArea.getWidth()) / 2;
    radius -= 5;
    float sum = 0;
    for (int i = 0; i < m_data->size(); ++i)
    {
        sum += m_data->at(i)->ydata[0];
    }

    float angle = 0;
    for (int i = 0; i < m_data->size(); ++i)
    {
        float normalized = m_data->at(i)->ydata[0] / sum;
        normalized *= 2*M_PI;
        float midAngle = normalized/2 + angle;
        DrawUtils<CRGB>::DrawPie(buf, m_data->at(i)->color, center, radius,
                                 angle, angle + normalized);
        CPoint<int> fillOffset(center.X() + cos(midAngle)*radius/2, center.Y() + sin(midAngle)*radius/2);
        DrawUtils<CRGB>::Fill(buf, m_data->at(i)->color, fillOffset);
        angle += normalized;
    }

}
