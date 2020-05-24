#ifndef TSTEXTPROPERTIES_H
#define TSTEXTPROPERTIES_H

#include "Colors.h"
#include "CPoint.h"
#include "string.h"

struct TextProperties
{
    void setText(const char *text);
    char *getText();
    CPoint<int> pos;
    bool isPosSetExt;
    CRGB color;
    TextProperties();

private:
    char *text;
};

struct WidgetTextFields
{
    TextProperties titleText;
    TextProperties xAxisText;
    TextProperties yAxisText;
};

#endif
