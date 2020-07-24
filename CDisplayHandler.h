#ifndef CDISPLAYHANDLER_H
#define CDISPLAYHANDLER_H

#include "CBuffer.h"
#include "Colors.h"

class IDisplayOwner
{
public:
    virtual void MouseMove(int x, int y) = 0;
    virtual void KeyPress(unsigned char key, bool pressed) = 0;
    virtual void MousePress(int x, int y, unsigned char key, bool pressed) = 0;
};

class CDisplayHandler
{
private:
    /* data */
public:
    CDisplayHandler(int windowWidth, int windowHeigth, const char *windowName, IDisplayOwner *owner = NULL);
    ~CDisplayHandler();
    bool Update(CBuffer<CRGB> &);
    CPoint<int> getLastMousePos();
    char *m_windowName;
    IDisplayOwner *m_owner;

private:
    CPoint<int> m_mousePos;
    static CDisplayHandler *theInstance;
    static void MouseMoveCallback(int event, int x, int y, int flag, void *param);
};

#endif