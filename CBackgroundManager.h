#ifndef CBACKGROUNDMANAGER_H
#define CBACKGROUNDMANAGER_H

#include "CBuffer.h"
#include "Colors.h"

class CBackgroundManager
{
public:
    CBackgroundManager();
    void Create(CBuffer<CRGB> itsCanvas);
    void Draw();
    CBuffer<CRGB> getActiveCanvas();

    void setTitle(const char* titleText);

private:
    CBuffer<CRGB> m_itsCanvas;

    struct TextProperties{
        char* text;
        CPoint<int> pos;
        bool isPosSetExt;
        CRGB color;
        TextProperties(): pos(0,0){
            text = NULL;
            isPosSetExt = false;
        }    
    };
    TextProperties m_widgetTitle;
    TextProperties m_xAxisLabel;
    TextProperties m_yAxisLabel;
    CRect<int> m_activeCanvasArea;
   

    //disallow cc and assignment op
    const CBackgroundManager operator=(const CBackgroundManager &);
    CBackgroundManager(const CBackgroundManager &);
};

#endif