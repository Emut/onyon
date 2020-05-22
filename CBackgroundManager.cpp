#include "CBackgroundManager.h"
#include "DrawUtils.h"
#include <string.h>

CBackgroundManager::CBackgroundManager() : m_itsCanvas(0, 0){}

void CBackgroundManager::Create(CBuffer<CRGB> itsCanvas)
{
    m_itsCanvas = itsCanvas;
    m_activeCanvasArea = CRect<int>(CPoint<int>(0, 0), m_itsCanvas.getSize());
}

CBuffer<CRGB> CBackgroundManager::getActiveCanvas()
{
    return CBuffer<CRGB>(m_itsCanvas, m_activeCanvasArea);
}

void CBackgroundManager::Draw()
{
    DrawUtils<CRGB>::DrawRectangle(m_itsCanvas,
                                   CRGB(0, 0, 0), CPoint<int>(0, 0),
                                   m_itsCanvas.getSize() - CPoint<int>(1, 1));

    if(m_widgetTitle.text != NULL)
    {
        DrawUtils<CRGB>::DrawString(m_itsCanvas, m_widgetTitle.color, m_widgetTitle.pos, m_widgetTitle.text);
    }
}

void CBackgroundManager::setTitle(const char *titleText)
{
    if (m_widgetTitle.text != NULL)
        delete[] m_widgetTitle.text;

    int titleLen = strlen(titleText);
    m_widgetTitle.text = new char[titleLen + 1];
    strcpy(m_widgetTitle.text, titleText);

    CPoint<int> titleSize = DrawUtils<CRGB>::getStringSize(titleText);
    if (!m_widgetTitle.isPosSetExt)
    {
        m_widgetTitle.pos.X() = (m_itsCanvas.getWidth() - titleSize.X()) / 2;
        m_widgetTitle.pos.Y() = 1;
    }
    m_activeCanvasArea.setTop(m_widgetTitle.pos.Y() + titleSize.Y() + 1);
}