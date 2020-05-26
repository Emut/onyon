#ifndef CCANVAS_H
#define CCANVAS_H

#include "IWidget.h"
#include "CBuffer.h"
#include "Colors.h"
#include "CDisplayHandler.h"
#include <vector>

class CCanvas: IDisplayOwner{
public:
    CCanvas(int canvasWidth, int canvasHeigth);

    int CreateWidget(CRect<int> position);
    int InsertLayer(int widgetID, const char* layerType, const void* args = NULL); 
    int InsertData(int widgetID, float* begin, float* end);
    int ReplaceData(int widgetID, int dataID, float* begin, float* end);
    bool RemoveData(int widgetID, int dataID);

    bool UpdateWidget(int widgetID);
    void UpdateAllWidgets();

    bool setWidgetBackgroundColor(int widgetID, CRGB color);
    bool setDataColor(int widgetID, int dataID, CRGB color);
    bool ExecuteSpecialLayerCmd(int widgetID, int layerID, void* command, void* args);

    bool DisplayOnScreen(bool enable, const char* screenName);
    bool SaveAsPgm(const char *fileName);
	bool SaveAsPpm(const char *fileName);

    bool setWidgetTitle(int widgetID, const char* titleText);


    void MouseMove(int x, int y);
    void KeyPress(unsigned char key, bool pressed);
    void MousePress(int x, int y, unsigned char key, bool pressed);

private:
    CBuffer<CRGB> m_itsCanvas;
    CDisplayHandler m_itsDisplay;
    std::vector<std::vector<ILayer*> > m_itsWidgets;
    std::vector<std::vector<CSeriesData*> > m_itsData;
    std::vector<CRect<int> > m_widgetAreas;
    std::vector<WidgetTextFields> m_widgetTexts;
    std::vector<CRGB> m_widgetBgColors;
    bool m_displayEnabled;
    
};

#endif