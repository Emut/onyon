#ifndef CCANVAS_H
#define CCANVAS_H

#include "IWidget.h"
#include "CBuffer.h"
#include "Colors.h"
#include "CDisplayHandler.h"
#include <vector>

class CCanvas : IDisplayOwner
{
public:
    CCanvas(int canvasWidth, int canvasHeigth);

    int CreateWidget(CRect<int> position);
    int InsertLayer(int widgetID, const char *layerType, const void *args = NULL);
    //int InsertData(int widgetID, float *begin, float *end);
    bool RemoveData(int widgetID, int dataID);

    template <class IterY>
    int InsertData(int widgetID, IterY y_begin, IterY y_end)
    {
        float *dummy = NULL;
        return InsertData(widgetID, y_begin, y_end, dummy, dummy);
    }

    template <class IterY, class IterX>
    int InsertData(int widgetID, IterY y_begin, IterY y_end, IterX x_begin, IterX x_end)
    {
        if (m_itsWidgets.size() <= widgetID)
            return -1;

        int newDataID = m_itsData[widgetID].size();
        CSeriesData *newSeries = new CSeriesData();
        newSeries->id = newDataID;
        m_itsData[widgetID].push_back(newSeries);

        int dataCount = 0;
        for (IterY it = y_begin; it != y_end; ++it)
        {
            ++dataCount;
        }
        newSeries->ydataCount = dataCount;
        if (dataCount != 0)
            newSeries->ydata = new float[dataCount];

        dataCount = 0;
        for (IterX it = x_begin; it != x_end; ++it)
        {
            ++dataCount;
        }
        newSeries->xdataCount = dataCount;
        if (dataCount != 0)
            newSeries->xdata = new float[dataCount];

        int i = 0;
        for (IterY it = y_begin; it != y_end; ++it)
        {
            newSeries->ydata[i++] = *it;
        }

        i = 0;
        for (IterX it = x_begin; it != x_end; ++it)
        {
            newSeries->xdata[i++] = *it;
        }

        newSeries->CalculateMaxima();
        char colorMask = newDataID % 6 + 1;
        newSeries->color.setRed(colorMask & 1 ? 255 : 0);
        newSeries->color.setBlue(colorMask & 2 ? 255 : 0);
        newSeries->color.setGreen(colorMask & 4 ? 255 : 0);
        char seriesName[50];
        sprintf(seriesName, "SERIES%d", newDataID);
        newSeries->setName(seriesName);
        return newDataID;
    }

    template <class IterY>
    int ReplaceData(int widgetID, int dataID, IterY y_begin, IterY y_end)
    {
        float *dummy = NULL;
        return ReplaceData(widgetID, dataID, y_begin, y_end, dummy, dummy);
    }

    template <class IterY, class IterX>
    int ReplaceData(int widgetID, int dataID, IterY y_begin, IterY y_end, IterX x_begin, IterX x_end)
    {
        if (m_itsWidgets.size() <= widgetID)
            return -1;
        if (m_itsData[widgetID].size() <= dataID)
            return -1;

        int newDataID = dataID; 
        CSeriesData *newSeries = m_itsData[widgetID][dataID];
        newSeries->id = newDataID;

        int dataCount = 0;
        for (IterY it = y_begin; it != y_end; ++it)
        {
            ++dataCount;
        }
        newSeries->ydataCount = dataCount;
        if (dataCount != 0)
            newSeries->ydata = new float[dataCount];

        dataCount = 0;
        for (IterX it = x_begin; it != x_end; ++it)
        {
            ++dataCount;
        }
        newSeries->xdataCount = dataCount;
        if (dataCount != 0)
            newSeries->xdata = new float[dataCount];

        int i = 0;
        for (IterY it = y_begin; it != y_end; ++it)
        {
            newSeries->ydata[i++] = *it;
        }

        i = 0;
        for (IterX it = x_begin; it != x_end; ++it)
        {
            newSeries->xdata[i++] = *it;
        }

        newSeries->CalculateMaxima();
        return newDataID;
    }

    bool UpdateWidget(int widgetID);
    void UpdateAllWidgets();

    bool setWidgetBackgroundColor(int widgetID, CRGB color);
    bool setDataColor(int widgetID, int dataID, CRGB color);
    bool setDataName(int widgetID, int dataID, const char *name);
    bool ExecuteSpecialLayerCmd(int widgetID, int layerID, void *command, void *args);

    bool DisplayOnScreen(bool enable, const char *screenName);
    bool SaveAsPgm(const char *fileName);
    bool SaveAsPpm(const char *fileName);

    bool setWidgetTitle(int widgetID, const char *titleText);
    bool setxAxisLabel(int widgetID, const char *labelText);
    bool setyAxisLabel(int widgetID, const char *labelText);

    void MouseMove(int x, int y);
    void KeyPress(unsigned char key, bool pressed);
    void MousePress(int x, int y, unsigned char key, bool pressed);

private:
    CBuffer<CRGB> m_itsCanvas;
    CDisplayHandler m_itsDisplay;
    std::vector<std::vector<ILayer *>> m_itsWidgets;
    std::vector<std::vector<CSeriesData *>> m_itsData;
    std::vector<CRect<int>> m_widgetAreas;
    std::vector<WidgetTextFields> m_widgetTexts;
    std::vector<CRGB> m_widgetBgColors;
    bool m_displayEnabled;
};

#endif