#include "CClockWidget.h"
#include "DrawUtils.h"

CClockWidget::CClockWidget()
{
    second = 0;
    minute = 0;
    hour = 0;
}

void CClockWidget::setData(std::vector<CSeriesData*> data){
    m_itsData = data;
}

void CClockWidget::Draw(CBuffer<CRGB> actCanvas)
{
    
    do
    {
        if (m_itsData.size() == 0)
            break;
        if (m_itsData[0]->dataCount < 1)
            break;
        hour = m_itsData[0]->ydata[0];
        if (m_itsData[0]->dataCount < 2)
            break;
        minute = m_itsData[0]->ydata[1];
        if (m_itsData[0]->dataCount < 3)
            break;
        second = m_itsData[0]->ydata[2];
    } while (false);
    
    DrawDial(actCanvas);
    DrawHands(actCanvas);
    return;
}

void CClockWidget::DrawDial(CBuffer<CRGB> actCanvas)
{
    //CBuffer<CRGB> actCanvas = m_bgMgr->getActiveCanvas();
    CPoint<int> clockCenter(actCanvas.getWidth() / 2, actCanvas.getHeigth() / 2);

    int outerRad = std::min(actCanvas.getWidth(), actCanvas.getHeigth()) / 2 - 5;
    DrawUtils<CRGB>::DrawCircle(actCanvas, CRGB(0, 0, 255),
                                clockCenter, 10);

    DrawUtils<CRGB>::DrawCircle(actCanvas, CRGB(0, 255, 0),
                                clockCenter, outerRad);

    int numberRadius = outerRad - 10;
    for (int i = 1; i < 13; ++i)
    {
        float angleOffset = i * 3.14 / 6 - 1.57;
        int xCenter = clockCenter.X() + numberRadius * cos(angleOffset);
        int yCenter = clockCenter.Y() + numberRadius * sin(angleOffset);
        CPoint<int> textCenter(xCenter, yCenter);

        char numberText[3];
        sprintf(numberText, "%d", i);
        CPoint<int> textSize = DrawUtils<CRGB>::getStringSize(numberText);
        CPoint<int> textTopLeft = textCenter - (textSize / 2);
        DrawUtils<CRGB>::DrawString(actCanvas, CRGB(255, 0, 0), textTopLeft, numberText);
    }
}
void CClockWidget::DrawHands(CBuffer<CRGB> actCanvas)
{

    //CBuffer<CRGB> actCanvas = m_bgMgr->getActiveCanvas();
    CPoint<int> clockCenter(actCanvas.getWidth() / 2, actCanvas.getHeigth() / 2);
    int outerRad = std::min(actCanvas.getWidth(), actCanvas.getHeigth()) / 2 - 5;
    float hourLenCoeff = 0.4;
    float minLenCoeff = 0.6;
    float secLenCoeff = 0.8;

    float shiftedMinute = minute + second / 60;
    float shiftedHour = hour + shiftedMinute / 60;

    float secAngle = 3.14f * second / 30 - 1.57f;
    DrawUtils<CRGB>::DrawLine(actCanvas, CRGB(255, 0, 0),
                              clockCenter.X(), clockCenter.Y(), secLenCoeff * outerRad, secAngle);

    float minAngle = 3.14f * shiftedMinute / 30 - 1.57f;
    DrawUtils<CRGB>::DrawLine(actCanvas, CRGB(0, 0, 0),
                              clockCenter.X(), clockCenter.Y(), minLenCoeff * outerRad, minAngle);

    float hourAngle = 3.14f * shiftedHour / 6 - 1.57f;
    DrawUtils<CRGB>::DrawLine(actCanvas, CRGB(0, 255, 0),
                              clockCenter.X(), clockCenter.Y(), hourLenCoeff * outerRad, hourAngle);
}