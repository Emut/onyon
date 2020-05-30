#include "CBackgroundManager.h"
#include "DrawUtils.h"
#include <string.h>
#include "CImageSaver.h"

CBackgroundManager::CBackgroundManager(const char* backgroundImageFile){
    backgroundImageBuf = NULL;
    if(backgroundImageFile != NULL){
        //const char* asd = backgroundImageFile;
        std::string fileNameStr = backgroundImageFile;
        CImageSaver::ReadFromPpm(backgroundImageBuf, fileNameStr);
    }
    m_bgColor = CRGB(255,255,255);
}

void CBackgroundManager::setTextProperties(WidgetTextFields *texts)
{
    m_textFields = texts;
}

void CBackgroundManager::Draw(CBuffer<CRGB> buf)
{
    if(backgroundImageBuf != NULL)
        buf.CopyFrom(*backgroundImageBuf);
    else
        buf.Fill(m_bgColor);
    m_activeCanvasArea = buf.getAreaRect();
    DrawUtils<CRGB>::DrawRectangle(buf,
                                   CRGB(0, 0, 0), buf.getAreaRect());
    
    m_activeCanvasArea.ShiftTop(1);
    m_activeCanvasArea.ShiftLeft(1);
    m_activeCanvasArea.ShiftBottom(-1);
    m_activeCanvasArea.ShiftRight(-1);

    if (m_textFields->titleText.getText() != NULL)
    {
        CPoint<int> titleSize = DrawUtils<CRGB>::getStringSize(m_textFields->titleText.getText());
        if (!m_textFields->titleText.isPosSetExt)
        {
            m_textFields->titleText.pos.X() = (buf.getWidth() - titleSize.X()) / 2;
            m_textFields->titleText.pos.Y() = 1;
        }
        DrawUtils<CRGB>::DrawString(buf, m_textFields->titleText.color, m_textFields->titleText.pos, m_textFields->titleText.getText());
        m_activeCanvasArea.ShiftTop(titleSize.Y() + 1);
    }
    return;
}

CRect<int> CBackgroundManager::getActiveArea(){
    return m_activeCanvasArea;
}

void CBackgroundManager::setBackgroundColor(CRGB color){
    m_bgColor = color;
}