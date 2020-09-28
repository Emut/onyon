#ifndef CBARGRAPHLAYER_H
#define CBARGRAPHLAYER_H

#include "ILayer.h"

class CBarGraphLayer : public ILayer
{
public:
    //param sets the orientation of the bars
    CBarGraphLayer(bool isVertical = true);

    void Draw(CBuffer<CRGB> buf);
    void setData(std::vector<CSeriesData *> *data);
    CRect<int> getActiveArea();

private:
    std::vector<CSeriesData *> *m_data;
    CRect<int> m_activeArea;
    bool m_isVertical;
};

#endif
