#include "ILayer.h"

//If not overridden, returns a rect with negative length and width
//Stating there is no area left after the draw of the layer
CRect<int> ILayer::getActiveArea()
{
    return CRect<int>(0, 0, -1, -1);
}

//method is vitrual to not force layers to implement.
//by default does nothing
void ILayer::SpecialCommand(void *command, void *args)
{
    return;
}

void ILayer::setTextProperties(WidgetTextFields *textFields)
{
    return;
}

void ILayer::setData(std::vector<CSeriesData*>* data)
{
    return;
}

ILayer::~ILayer()
{
}

void ILayer::setBackgroundColor(CRGB color){
    
}