#include "CClockWidget.h"
#include "DrawUtils.h"

CClockWidget::CClockWidget()
{
    m_itsData = NULL;
    m_dialOuterColor = CRGB(0, 255, 0);
    m_dialInnerColor = CRGB(0, 255, 0);
    m_numberColor = CRGB(255, 0, 0);
}

void CClockWidget::setData(std::vector<CSeriesData *> *data)
{
    m_itsData = data;
}

void CClockWidget::Draw(CBuffer<CRGB> actCanvas)
{
    hour.valid = false;
    minute.valid = false;
    second.valid = false;
    do
    {
        if (m_itsData->size() == 0)
            break;
        hour.time = (*m_itsData)[0]->ydata[0];
        hour.color = (*m_itsData)[0]->color;
        hour.valid = true;
        if ((*m_itsData).size() == 1)
            break;
        minute.time = (*m_itsData)[1]->ydata[0];
        minute.color = (*m_itsData)[1]->color;
        minute.valid = true;
        if ((*m_itsData).size() == 2)
            break;
        second.time = (*m_itsData)[2]->ydata[0];
        second.color = (*m_itsData)[2]->color;
        second.valid = true;
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
    DrawUtils<CRGB>::DrawCircle(actCanvas, m_dialInnerColor,
                                clockCenter, 10);

    DrawUtils<CRGB>::DrawCircle(actCanvas, m_dialOuterColor,
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
        DrawUtils<CRGB>::DrawString(actCanvas, m_numberColor, textTopLeft, numberText);
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

    float shiftedMinute = minute.time + second.time / 60;
    float shiftedHour = hour.time + shiftedMinute / 60;

    if (second.valid)
    {
        float secAngle = 3.14f * second.time / 30 - 1.57f;
        DrawUtils<CRGB>::DrawLine(actCanvas, second.color,
                                  clockCenter.X(), clockCenter.Y(), secLenCoeff * outerRad, secAngle);
    }

    if (minute.valid)
    {
        float minAngle = 3.14f * shiftedMinute / 30 - 1.57f;
        DrawUtils<CRGB>::DrawLine(actCanvas, minute.color,
                                  clockCenter.X(), clockCenter.Y(), minLenCoeff * outerRad, minAngle);
        DrawUtils<CRGB>::DrawLine(actCanvas, minute.color,
                                  clockCenter.X() - 1, clockCenter.Y(), minLenCoeff * outerRad, minAngle);
        DrawUtils<CRGB>::DrawLine(actCanvas, minute.color,
                                  clockCenter.X() + 1, clockCenter.Y(), minLenCoeff * outerRad, minAngle);
    }

    if (hour.valid)
    {
        float hourAngle = 3.14f * shiftedHour / 6 - 1.57f;
        DrawUtils<CRGB>::DrawLine(actCanvas, hour.color,
                                  clockCenter.X(), clockCenter.Y(), hourLenCoeff * outerRad, hourAngle);
        DrawUtils<CRGB>::DrawLine(actCanvas, hour.color,
                                  clockCenter.X() - 1, clockCenter.Y(), hourLenCoeff * outerRad, hourAngle);
        DrawUtils<CRGB>::DrawLine(actCanvas, hour.color,
                                  clockCenter.X() + 1, clockCenter.Y(), hourLenCoeff * outerRad, hourAngle);
    }
}

void CClockWidget::SpecialCommand(void *command, void *args)
{
    int commandID = *((int *)command);
    switch (commandID)
    {
    case 0:
        m_numberColor = *((CRGB *)args);
        break;
    
    case 1:
        m_dialInnerColor = *((CRGB *)args);
        break;
    
    case 2:
        m_dialOuterColor = *((CRGB *)args);
        break;
    }
}