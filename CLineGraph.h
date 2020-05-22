#ifndef CLINEGRAPH_H
#define CLINEGRAPH_H
#include "IWidget.h"
#include "CBackgroundManager.h"

class CLineGraph : public IWidget
{
public:
    CLineGraph();
    void Create(CBuffer<CRGB> itsCanvas);
    void Draw(const std::vector<CSeriesData*>& data);

private:
    CBuffer<CRGB> m_itsCanvas;
    CBackgroundManager m_itsBgManager;
};

#endif