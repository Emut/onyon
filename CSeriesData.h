#ifndef CSERIESDATA_H
#define CSERIESDATA_H

#include "Colors.h"

class CSeriesData
{
public:
    int id;
    float y_min, y_max, x_min, x_max;
    CRGB color;
    int dataCount;
    float *ydata, *xdata;
    CSeriesData();
    ~CSeriesData();
    CSeriesData(const CSeriesData &);
    CSeriesData &operator=(const CSeriesData &);
};

#endif
