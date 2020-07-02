#ifndef CLINEGRAPH_H
#define CLINEGRAPH_H
#include "ILayer.h"
#include "CBackgroundManager.h"

class CLineGraph : public ILayer
{
public:
    CLineGraph();
    void Create(CBuffer<CRGB> itsCanvas);
    void Draw(const std::vector<CSeriesData*>& data);
    void Draw(CBuffer<CRGB> buf);
    void setData(std::vector<CSeriesData*>* data);
    CRect<int> getActiveArea();

private:
    std::vector<CSeriesData*>* m_data;
    CPoint<float> NormalizePoint(CRect<float> areaFrom, CRect<int> areaTo, CPoint<float> point);
    CRect<int> m_activeArea;
};

#endif