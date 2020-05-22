#include "CSeriesData.h"
#include <string.h>

CSeriesData::CSeriesData()
{
    id = -1;
    y_max = 0;
    y_min = 0;
    x_max = 0;
    x_min = 0;
    color = CRGB(128, 128, 128);
    dataCount = 0;
    ydata = NULL;
    xdata = NULL;
}

CSeriesData &CSeriesData::operator=(const CSeriesData &rhs)
{
    return *this;
}

CSeriesData::CSeriesData(const CSeriesData &rhs)
{
    id = rhs.id;
    y_max = rhs.y_max;
    y_min = rhs.y_min;
    x_max = rhs.x_max;
    x_min = rhs.x_min;
    color = rhs.color;
    dataCount = rhs.dataCount;
    xdata = new float[dataCount];
    ydata = new float[dataCount];
    for (int i = 0; i < dataCount; ++i)
    {
        xdata[i] = rhs.xdata[i];
        ydata[i] = rhs.ydata[i];
    }
}

CSeriesData::~CSeriesData(){
    if (xdata != NULL)
        delete[] xdata;
    if (ydata != NULL)
        delete[] ydata;
}
