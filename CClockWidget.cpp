#include "CClockWidget.h"
#include "DrawUtils.h"

CClockWidget::CClockWidget() : m_itsCanvas(0, 0)
{
    second = 0;
    minute = 0;
    hour = 0;
}

void CClockWidget::Create(CBuffer<CRGB> itsCanvas)
{
    m_itsCanvas = itsCanvas;
    m_bgMgr->Create(m_itsCanvas);
}
void CClockWidget::Draw(const std::vector<CSeriesData *> &data)
{
    m_itsCanvas.Fill(CRGB(255,255,255));
    m_bgMgr->Draw();
    CBuffer<CRGB> actCanvas = m_bgMgr->getActiveCanvas();

    do
    {
        if (data.size() == 0)
            break;
        if (data[0]->dataCount < 1)
            break;
        hour = data[0]->ydata[0];
        if (data[0]->dataCount < 2)
            break;
        minute = data[0]->ydata[1];
        if (data[0]->dataCount < 3)
            break;
        second = data[0]->ydata[2];
    } while (false);

    DrawDial();
    DrawHands();
    return;
}

void CClockWidget::DrawDial()
{
    CBuffer<CRGB> actCanvas = m_bgMgr->getActiveCanvas();
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
void CClockWidget::DrawHands()
{

    CBuffer<CRGB> actCanvas = m_bgMgr->getActiveCanvas();
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