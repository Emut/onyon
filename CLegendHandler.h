#ifndef CLEGENDHANDLER_H
#define CLEGENDHANDLER_H

#include "ILayer.h"

class CLegendHandler : public ILayer
{
public:
    CLegendHandler();
    void setData(std::vector<CSeriesData *> *data);
    void Draw(CBuffer<CRGB> buf);
    CRect<int> getActiveArea();

private:
    std::vector<CSeriesData *> *m_data;
    CRect<int> m_activeArea;
    CRGB m_colorBackground;
    CRGB m_colorBorder;
    enum Marker{
        NONE,
        LINE,
        BOX
    };
    Marker m_marker;
    CPoint<int> m_markerSize;
};

#endif