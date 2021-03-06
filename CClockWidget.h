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
    void setData(std::vector<CSeriesData*>* data);
    void SpecialCommand(void *command, void *args);

private:
    void DrawDial(CBuffer<CRGB> actCanvas);
    void DrawHands(CBuffer<CRGB> actCanvas);

    std::vector<CSeriesData*>* m_itsData;

    struct HandData{
        float time;
        bool valid;
        CRGB color;
    };

    HandData hour;
    HandData minute;
    HandData second;
    CRGB m_dialOuterColor;
    CRGB m_dialInnerColor;
    CRGB m_numberColor;
};



#endif