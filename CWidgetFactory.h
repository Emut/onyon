#ifndef CWIDGETFACTORY_H
#define CWIDGETFACTORY_H

#include "IWidget.h"


class CWidgetFactory
{
public:
    static IWidget *getWidget(const char *widgetType);
};

#endif
