#ifndef CBACKGROUNDMANAGER_H
#define CBACKGROUNDMANAGER_H

#include "CBuffer.h"
#include "Colors.h"
#include "ILayer.h"
#include "tsTextProperties.h"

class CBackgroundManager: public ILayer
{
public:
    //CBackgroundManager();

    void Draw(CBuffer<CRGB> buf);
    void setTextProperties(WidgetTextFields* texts);
    CRect<int> getActiveArea();

private:
    WidgetTextFields* m_textFields;
    CRect<int> m_activeCanvasArea;
   

    //disallow cc and assignment op
    //const CBackgroundManager operator=(const CBackgroundManager &);
    //CBackgroundManager(const CBackgroundManager &);
};

#endif