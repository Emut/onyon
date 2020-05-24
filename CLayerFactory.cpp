#include "CLayerFactory.h"
#include "CClockWidget.h"
#include "CLineGraph.h"
#include "CBackgroundManager.h"

#include <string.h>
ILayer *CWidgetFactory::getLayer(const char *widgetType)
{
    ILayer *createdInstance = NULL;
    do
    {
        if (strcmp(widgetType, "BackgroundManager") == 0)
        {
            createdInstance = new CBackgroundManager();
            break;
        }
        if (strcmp(widgetType, "AnalogClock") == 0)
        {
            createdInstance = new CClockWidget();
            break;
        }
        /*
        if (strcmp(widgetType, "LineGraph") == 0){
            createdInstance = new CLineGraph();
            break;
        }*/
        //matches nothing
        return NULL;
    } while (false);
    
    return createdInstance;
}