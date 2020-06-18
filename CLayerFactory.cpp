#include "CLayerFactory.h"
#include "CClockWidget.h"
#include "CLineGraph.h"
#include "CBackgroundManager.h"
#include "CMouseKeyboardSampleLayer.h"
#include "C2dPlotAxisHandler.h"

#include <string.h>
ILayer *CWidgetFactory::getLayer(const char *widgetType, const void *args)
{
    ILayer *createdInstance = NULL;
    do
    {
        if (strcmp(widgetType, "BackgroundManager") == 0)
        {
            createdInstance = new CBackgroundManager((const char *)args);
            break;
        }
        if (strcmp(widgetType, "AnalogClock") == 0)
        {
            createdInstance = new CClockWidget();
            break;
        }

        if (strcmp(widgetType, "LineGraph") == 0)
        {
            createdInstance = new CLineGraph();
            break;
        }

        if (strcmp(widgetType, "MouseKeyboardSample") == 0)
        {
            createdInstance = new CMouseKeyboardSampleLayer();
            break;
        }

        if (strcmp(widgetType, "2dAxisHandler") == 0)
        {
            createdInstance = new C2dPlotAxisHandler();
            break;
        }
        //matches nothing
        return NULL;
    } while (false);

    return createdInstance;
}