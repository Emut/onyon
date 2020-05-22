#ifndef CCLOCKWIDGET_H
#define CCLOCKWIDGET_H

#include "IWidget.h"
//#include "CBackgroundManager.h"

class CClockWidget : public IWidget
{
public:
    CClockWidget();
    void Create(CBuffer<CRGB> itsCanvas);
    void Draw(const std::vector<CSeriesData*> &data);

private:
    void DrawDial();
    void DrawHands();

    CBuffer<CRGB> m_itsCanvas;
    //CBackgroundManager m_itsBgManager;
    float hour;
    float minute;
    float second;
};

#endif