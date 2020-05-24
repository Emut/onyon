#ifndef CWIDGETFACTORY_H
#define CWIDGETFACTORY_H

#include "ILayer.h"


class CWidgetFactory
{
public:
    static ILayer *getLayer(const char *layerType);
};

#endif
