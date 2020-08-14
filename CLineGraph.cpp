#include "CLineGraph.h"
#include "DrawUtils.h"

CLineGraph::CLineGraph() {}

void CLineGraph::Draw(CBuffer<CRGB> buf)
{
    m_activeArea = buf.getAreaRect();
    if (m_data->size() == 0)
        return;
    //find the overall maxima for all series
    CRect<float> dataArea;
    dataArea.setLeft((*m_data)[0]->xdataCount == 0 ? 1 : (*m_data)[0]->x_min);
    dataArea.setTop((*m_data)[0]->y_min);
    dataArea.setRight((*m_data)[0]->xdataCount == 0 ? (*m_data)[0]->ydataCount : (*m_data)[0]->x_max);
    dataArea.setBottom((*m_data)[0]->y_max);
    for (int i = 1; i < m_data->size(); ++i)
    {
        CSeriesData *data = (*m_data)[i];
        float left = (*m_data)[i]->xdataCount == 0 ? 1 : (*m_data)[i]->x_min;
        if (left < dataArea.getLeft())
            dataArea.setLeft(left);
        float right = (*m_data)[i]->xdataCount == 0 ? (*m_data)[i]->ydataCount : (*m_data)[i]->x_max;
        if (right > dataArea.getRight())
            dataArea.setRight(right);

        if ((*m_data)[i]->y_min < dataArea.getTop())
            dataArea.setTop((*m_data)[i]->y_min);
        if ((*m_data)[i]->y_max > dataArea.getBottom())
            dataArea.setBottom((*m_data)[i]->y_max);
    }

    for (int i = 0; i < m_data->size(); ++i)
    {
        
        CSeriesData *seriesData = (*m_data)[i];
        CPoint<float> prevPnt(seriesData->xdataCount == 0 ? 1 : seriesData->xdata[0], seriesData->ydata[0]);
        prevPnt = NormalizePoint(dataArea, buf.getAreaRect(), prevPnt);
        for (int j = 1; j < seriesData->ydataCount; ++j)
        {
            CPoint<float> currentPnt(0, seriesData->ydata[j]);
            if (seriesData->xdataCount != 0)
            {
                currentPnt.x = seriesData->xdata[j];
            }
            else
            {
                currentPnt.x = j + 1;
            }
            currentPnt = NormalizePoint(dataArea, buf.getAreaRect(), currentPnt);
            DrawUtils<CRGB>::DrawLine(buf, seriesData->color, currentPnt, prevPnt);
            prevPnt = currentPnt;
        }
    }
}

void CLineGraph::setData(std::vector<CSeriesData *> *data)
{
    m_data = data;
}

CPoint<float> CLineGraph::NormalizePoint(CRect<float> areaFrom, CRect<int> areaTo, CPoint<float> point)
{
    CPoint<float> retVal(0, 0);
    retVal.x = (point.x - areaFrom.getLeft()) / (areaFrom.getWidth() - 1) * (areaTo.getWidth() - 1);
    retVal.y = (areaTo.getHeigth() - 1) - (point.y - areaFrom.getTop()) / (areaFrom.getHeigth() - 1) * (areaTo.getHeigth() - 1);

    return retVal;
}

CRect<int> CLineGraph::getActiveArea()
{
    return m_activeArea;
}