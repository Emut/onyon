#include "CMouseKeyboardSampleLayer.h"
#include "DrawUtils.h"

void CMouseKeyboardSampleLayer::Draw(CBuffer<CRGB> buf)
{
    char toWrite[30];
    sprintf(toWrite, "MOUSE@%d,%d", m_MousePos.x, m_MousePos.y);
    DrawUtils<CRGB>::DrawString(buf, CRGB(255,0,0), CPoint<int>(0,0), toWrite);
    CPoint<int> textSize = DrawUtils<CRGB>::getStringSize(toWrite);

    sprintf(toWrite, "KEY@%d,%s", (int)m_key, m_isPressed?"PRESS":"RELEASE");
    DrawUtils<CRGB>::DrawString(buf, CRGB(255,0,0), CPoint<int>(0,textSize.y + 1), toWrite);    
}
bool CMouseKeyboardSampleLayer::MouseMove(int x, int y)
{
    m_MousePos = CPoint<int>(x,y);
    return true;
}
bool CMouseKeyboardSampleLayer::KeyPress(unsigned char key, bool pressed)
{
    m_key = key;
    m_isPressed = pressed;
    return true;
}

CMouseKeyboardSampleLayer::CMouseKeyboardSampleLayer(): m_MousePos(0,0){
    m_key = 0;
    m_isPressed = false;
}