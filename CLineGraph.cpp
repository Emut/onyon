#include "CLineGraph.h"
#include "DrawUtils.h"

CLineGraph::CLineGraph() {}

void CLineGraph::Draw(CBuffer<CRGB> buf)
{
    //buf.Fill(CRGB(255, 0, 0));
    //return;
    if (m_data->size() == 0)
        return;
    //find the overall maxima for all series
    CRect<float> dataArea;
    dataArea.setLeft((*m_data)[0]->x_min);
    dataArea.setTop((*m_data)[0]->y_min);
    dataArea.setRight((*m_data)[0]->x_max);
    dataArea.setBottom((*m_data)[0]->y_max);
    for (int i = 1; i < m_data->size(); ++i)
    {
        CSeriesData *data = (*m_data)[i];
        if ((*m_data)[i]->x_min < dataArea.getLeft())
            dataArea.setLeft((*m_data)[i]->x_min);
        if ((*m_data)[i]->y_min < dataArea.getTop())
            dataArea.setTop((*m_data)[i]->y_min);
        if ((*m_data)[i]->x_max > dataArea.getRight())
            dataArea.setLeft((*m_data)[i]->x_max);
        if ((*m_data)[i]->y_max > dataArea.getBottom())
            dataArea.setTop((*m_data)[i]->y_max);
    }

    for (int i = 0; i < m_data->size(); ++i)
    {
        CPoint<float> prevPnt(0, 0);
        CSeriesData *seriesData = (*m_data)[i];
        if (seriesData->xdataCount != 0)
        {
            int dataCount = std::min(seriesData->ydataCount, seriesData->xdataCount);
            for (int j = 0; j < seriesData->ydataCount; ++j)
            {
                CPoint<float> currentPnt(seriesData->xdata[j], seriesData->ydata[j]);
                currentPnt = NormalizePoint(dataArea, buf.getAreaRect(), currentPnt);
                DrawUtils<CRGB>::DrawLine(buf, seriesData->color, currentPnt, prevPnt);
                prevPnt = currentPnt;
            }
        }
        else
        {
            //since x data will not be used, dataArea need to be updated.
            dataArea.setLeft(1);
            dataArea.setRight(seriesData->ydataCount);
            for (int j = 0; j < seriesData->ydataCount; ++j)
            {
                CPoint<float> currentPnt(j + 1, seriesData->ydata[j]);
                currentPnt = NormalizePoint(dataArea, buf.getAreaRect(), currentPnt);
                DrawUtils<CRGB>::DrawLine(buf, seriesData->color, currentPnt, prevPnt);
                prevPnt = currentPnt;
            }
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
    retVal.X() = (point.X() - areaFrom.getLeft()) / (areaFrom.getWidth()-1) * (areaTo.getWidth() - 1);
    retVal.Y() = (point.Y() - areaFrom.getTop()) / (areaFrom.getHeigth() -1) * (areaTo.getHeigth() - 1);

    return retVal;
}