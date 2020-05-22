#include "CCanvas.h"
#include "CImageSaver.h"
#include "CWidgetFactory.h"

CCanvas::CCanvas(int canvasWidth, int canvasHeigth) : m_itsCanvas(canvasWidth, canvasHeigth),
                                                      m_itsDisplay(canvasWidth, canvasHeigth, "Name")
{
    m_itsCanvas.Fill(CRGB(255, 255, 255));
    m_displayEnabled = false;
}

bool CCanvas::SaveAsPgm(const char *fileName)
{
    return CImageSaver::SaveAsPgm(m_itsCanvas, fileName);
}

bool CCanvas::SaveAsPpm(const char *fileName)
{
    return CImageSaver::SaveAsPpm(m_itsCanvas, fileName);
}

int CCanvas::CreateWidget(const char *widgetType, CRect<int> position)
{
    IWidget *newWidget = CWidgetFactory::getWidget(widgetType);
    if (newWidget == NULL)
        return -1; //not found in factory.

    int widgetID = m_itsWidgets.size();
    m_itsWidgets.push_back(newWidget);
    std::vector<CSeriesData *> tempData;
    m_itsData.push_back(tempData);
    newWidget->Create(CBuffer<CRGB>(m_itsCanvas, position));

    return widgetID;
}

int CCanvas::InsertData(int widgetID, float *begin, float *end)
{
    if (m_itsWidgets.size() <= widgetID && m_itsWidgets[widgetID] == NULL)
        return -1;

    int newDataID = m_itsData[widgetID].size();
    CSeriesData *newSeries = new CSeriesData();
    m_itsData[widgetID].push_back(newSeries);

    int dataCount = 0;
    for (float *it = begin; it != end; ++it)
    {
        ++dataCount;
    }
    newSeries->dataCount = dataCount;
    newSeries->id = newDataID;
    newSeries->ydata = new float[dataCount];
    newSeries->xdata = new float[dataCount];
    int i = 0;
    for (float *it = begin; it != end; ++it)
    {
        newSeries->ydata[i++] = *it;
    }

    return newDataID;
}

int CCanvas::ReplaceData(int widgetID, int dataID, float *begin, float *end)
{
    if (m_itsWidgets.size() <= widgetID && m_itsWidgets[widgetID] == NULL)
        return -1;
    //if said data does not exist, insert it
    if (m_itsData.size() <= dataID)
        return InsertData(widgetID, begin, end);

    int dataCount = 0;
    for (float *it = begin; it != end; ++it)
    {
        ++dataCount;
    }
    //if new and old data are at the same size, omit deletion
    //just overwrite
    if (dataCount == m_itsData[widgetID][dataID]->dataCount)
    {
        int i = 0;
        for (float *it = begin; it != end; ++it)
        {
            m_itsData[widgetID][dataID]->ydata[i++] = *it;
        }
    }
    return dataID;
}

bool CCanvas::UpdateWidget(int widgetID)
{
    if (m_itsWidgets.size() <= widgetID && m_itsWidgets[widgetID] == NULL)
        return false;
    m_itsWidgets[widgetID]->Draw(m_itsData[widgetID]);
    if (m_displayEnabled)
        m_itsDisplay.Update(m_itsCanvas);
    return true;
}
void CCanvas::UpdateAllWidgets()
{
    for (int i = 0; i < m_itsWidgets.size(); ++i)
        UpdateWidget(i);
}

bool CCanvas::DisplayOnScreen(bool enable, const char *screenName)
{
    m_displayEnabled = enable;
    return true;
}

bool CCanvas::setWidgetTitle(int widgetID, const char* titleText){
    if (m_itsWidgets.size() <= widgetID && m_itsWidgets[widgetID] == NULL)
        return false;
    return m_itsWidgets[widgetID]->setTitle(titleText);
}