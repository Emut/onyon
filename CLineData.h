#include "Colors.h"

class LineData
{
public:
 
    int id;
    float y_min, y_max, x_min, x_max;
    CRGB color;
    int dataCount;
    float *ydata, *xdata;

    enum teDataPointMark
    {
        DPM_NONE,
        DPM_CIRCLE,
        DPM_CROSS,
        DPM_SQUARE
    };

    teDataPointMark dataPointMarker;

    LineData(const LineData &);
    LineData &operator=(const LineData &);
    LineData();
    ~LineData();
};
