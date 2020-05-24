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
    virtual void setData(std::vector<CSeriesData*> data);

    //fields such as title, x and y axis labels
    virtual void setTextProperties(WidgetTextFields *texts);

    //because the layers vary greatly in purpose, a generic
    //function to execute special functions through the interface
    virtual void SpecialCommand(void *command, void *args);

    virtual ~ILayer();
};

#endif