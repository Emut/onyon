#ifndef CPIECHARTLAYER_H
#define CPIECHARTLAYER_H
#include "ILayer.h"

class CPieChartLayer : public ILayer
{
    void Draw(CBuffer<CRGB> buf);
    void setData(std::vector<CSeriesData *> *data);
    CRect<int> getActiveArea();

private:
    std::vector<CSeriesData *> *m_data;
    CRect<int> m_activeArea;
};

#endif
