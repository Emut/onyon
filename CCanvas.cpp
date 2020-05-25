#include "CCanvas.h"
#include "CImageSaver.h"
#include "CLayerFactory.h"

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

int CCanvas::CreateWidget(CRect<int> position)
{

    int widgetID = m_itsWidgets.size();

    //initialize the vectors for various data
    std::vector<ILayer *> tempLayers;
    m_itsWidgets.push_back(tempLayers);
    std::vector<CSeriesData *> tempData;
    m_itsData.push_back(tempData);
    m_widgetAreas.push_back(position);
    WidgetTextFields tempTexts;
    m_widgetTexts.push_back(tempTexts);
    m_widgetBgColors.push_back(CRGB(255,255,255));

    return widgetID;
}

int CCanvas::InsertLayer(int widgetID, const char *layerType)
{
    if (m_itsWidgets.size() <= widgetID)
        return -1; //widget does not exist.

    ILayer *newLayer = CWidgetFactory::getLayer(layerType);
    if (newLayer == NULL)
        return -1; //not found in factory.

    m_itsWidgets[widgetID].push_back(newLayer);
    return m_itsWidgets[widgetID].size() - 1;
}

int CCanvas::InsertData(int widgetID, float *begin, float *end)
{
    if (m_itsWidgets.size() <= widgetID)
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
    if (m_itsWidgets.size() <= widgetID)
        return -1;
    //if said data does not exist, insert it
    if (m_itsData[widgetID].size() <= dataID)
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
    if (m_itsWidgets.size() <= widgetID)
        return false;

    CRect<int> drawArea = m_widgetAreas[widgetID];
    for (int j = 0; j < m_itsWidgets[widgetID].size(); ++j)
    {
        ILayer *currentLayer = m_itsWidgets[widgetID][j];
        currentLayer->setData(&m_itsData[widgetID]);
        currentLayer->setTextProperties(&m_widgetTexts[widgetID]);
        currentLayer->Draw(CBuffer<CRGB>(m_itsCanvas, drawArea));
        drawArea = currentLayer->getActiveArea();
        int w = drawArea.getWidth();
        int h = drawArea.getHeigth();
        if (drawArea.getHeigth() <= 0 || drawArea.getWidth() <= 0)
        {
            break;
        }
        drawArea += m_widgetAreas[widgetID].getTopLeft();
    }

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

bool CCanvas::setWidgetTitle(int widgetID, const char *titleText)
{
    if (m_widgetTexts.size() <= widgetID)
        return false;

    m_widgetTexts[widgetID].titleText.setText(titleText);
    return true;
}

bool CCanvas::setDataColor(int widgetID, int dataID, CRGB color){
    if (m_itsWidgets.size() <= widgetID)
        return false;
    
    if (m_itsData[widgetID].size() <= dataID)
        return false;

    m_itsData[widgetID][dataID]->color = color;
    return true;
}

bool CCanvas::setWidgetBackgroundColor(int widgetID, CRGB color){
    if (m_itsWidgets.size() <= widgetID)
        return false;
    m_widgetBgColors[widgetID] = color;

    for(int i = 0; i < m_itsWidgets[widgetID].size(); ++i)
        m_itsWidgets[widgetID][i]->setBackgroundColor(color);

    return true;
}