#ifndef CDISPLAYHANDLER_H
#define CDISPLAYHANDLER_H

#include "CBuffer.h"
#include "Colors.h"

class CDisplayHandler
{
private:
    /* data */
public:
    CDisplayHandler(int windowWidth, int windowHeigth, const char *windowName);
    ~CDisplayHandler();
    bool Update(CBuffer<CRGB>&);
    char *windowName;
};



#endif