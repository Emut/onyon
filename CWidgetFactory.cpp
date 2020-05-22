#include "CWidgetFactory.h"
#include "CClockWidget.h"
#include "CLineGraph.h"

#include <string.h>
IWidget *CWidgetFactory::getWidget(const char *widgetType)
{
    IWidget *createdInstance = NULL;
    do
    {
        if (strcmp(widgetType, "AnalogClock") == 0)
        {
            createdInstance = new CClockWidget();
            break;
        }
        if (strcmp(widgetType, "LineGraph") == 0){
            createdInstance = new CLineGraph();
            break;
        }
        //matches nothing
        return NULL;
    } while (false);
    //hardcoded for now, since there is only 1 bgManager
    createdInstance->m_bgMgr = new CBackgroundManager();
    return createdInstance;
}