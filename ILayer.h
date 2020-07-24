#ifndef ILAYER_H
#define ILAYER_H

#include "CRect.h"
#include "CBuffer.h"
#include "Colors.h"
#include "tsTextProperties.h"
#include <vector>
#include "CSeriesData.h"

class ILayer
{
public:
    //Draws the layer to given buffer.
    virtual void Draw(CBuffer<CRGB> buf) = 0;

    //returns the area left after drawing the layer.
    virtual CRect<int> getActiveArea();

    //
    virtual void setData(std::vector<CSeriesData*>* data);

    //fields such as title, x and y axis labels
    virtual void setTextProperties(WidgetTextFields *texts);

    virtual void setBackgroundColor(CRGB color);

    //update functions for mouse and keyboard functions
    //if layer returns true, it means layer is updated 
    //and would need to be refreshed (i.e. redrawn)
    virtual bool MouseMove(int x, int y);
    virtual bool KeyPress(unsigned char key, bool pressed);
    virtual bool MousePress(int x, int y, unsigned char key, bool pressed);

    //because the layers vary greatly in purpose, a generic
    //function to execute special functions through the interface
    virtual void SpecialCommand(void *command, void *args);

    virtual ~ILayer();
};


#endif