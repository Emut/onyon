#ifndef IWIDGET_H
#define IWIDGET_H

#include "CSeriesData.h"
#include "CBuffer.h"
#include <vector>
#include "CBackgroundManager.h"

class IWidget
{

public:
    CBackgroundManager *m_bgMgr;
    virtual void Create(CBuffer<CRGB> itsCanvas) = 0;
    virtual void Draw(const std::vector<CSeriesData *> &data) = 0;

    virtual bool setTitle(const char *titleText);
};

#endif
