#ifndef CMOUSEKEYBOARDSAMPLELAYER_H
#define CMOUSEKEYBOARDSAMPLELAYER_H

#include "ILayer.h"

class CMouseKeyboardSampleLayer : public ILayer
{
public:
    CMouseKeyboardSampleLayer();
    void Draw(CBuffer<CRGB> buf);
    bool MouseMove(int x, int y);
    bool KeyPress(unsigned char key, bool pressed);

    private:
    CPoint<int> m_MousePos;
    unsigned char m_key;
    bool m_isPressed;
};

#endif
