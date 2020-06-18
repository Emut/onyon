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
    xdataCount = 0;
    ydataCount = 0;
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
    xdataCount = rhs.xdataCount;
    ydataCount = rhs.ydataCount;
    xdata = new float[xdataCount];
    ydata = new float[ydataCount];
    for (int i = 0; i < xdataCount; ++i)
    {
        xdata[i] = rhs.xdata[i];
    }
    for (int i = 0; i < ydataCount; ++i)
    {
        ydata[i] = rhs.ydata[i];
    }
}

CSeriesData::~CSeriesData(){
    if (xdata != NULL)
        delete[] xdata;
    if (ydata != NULL)
        delete[] ydata;
}

void CSeriesData::CalculateMaxima(){
    if(xdataCount != 0){
        x_min = xdata[0];
        x_max = xdata[0];
        for(int i = 1; i < xdataCount; ++i){
            if(xdata[i] < x_min)
                x_min = xdata[i];
            if(xdata[i] > x_max)
                x_max = xdata[i];
        }
    }
    if(ydataCount != 0){
        y_min = ydata[0];
        y_max = ydata[0];
        for(int i = 1; i < ydataCount; ++i){
            if(ydata[i] < y_min)
                y_min = ydata[i];
            if(ydata[i] > y_max)
                y_max = ydata[i];
        }
    }
}
