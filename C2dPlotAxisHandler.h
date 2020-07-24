#ifndef C2DPLOTAXISHANDLER_H
#define C2DPLOTAXISHANDLER_H

#include "ILayer.h"

class C2dPlotAxisHandler: public ILayer{
public:
    virtual void setTextProperties(WidgetTextFields *texts);
    virtual void setData(std::vector<CSeriesData*>* data);
    virtual CRect<int> getActiveArea();
    void Draw(CBuffer<CRGB> buf);
private:
    std::vector<CSeriesData*>* m_data;
    WidgetTextFields* m_texts;
    CRect<int> m_activeArea;
};


#endif