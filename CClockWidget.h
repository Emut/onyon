#ifndef CCLOCKWIDGET_H
#define CCLOCKWIDGET_H

#include "IWidget.h"
//#include "CBackgroundManager.h"

class CClockWidget : public ILayer
{
public:
    CClockWidget();
    void Create(CBuffer<CRGB> itsCanvas);
    void Draw(CBuffer<CRGB> actCanvas);
    void setData(std::vector<CSeriesData*> data);

private:
    void DrawDial(CBuffer<CRGB> actCanvas);
    void DrawHands(CBuffer<CRGB> actCanvas);

    std::vector<CSeriesData*> m_itsData;
    float hour;
    float minute;
    float second;
};

#endif