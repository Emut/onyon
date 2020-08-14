#include "CCanvas.h"
#include "CImageSaver.h"
#include "CLayerFactory.h"

CCanvas::CCanvas(int canvasWidth, int canvasHeigth) : m_itsCanvas(canvasWidth, canvasHeigth),
                                                      m_itsDisplay(canvasWidth, canvasHeigth, "Name", this)
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
    m_widgetBgColors.push_back(CRGB(255, 255, 255));

    return widgetID;
}

int CCanvas::InsertLayer(int widgetID, const char *layerType, const void *args)
{
    if (m_itsWidgets.size() <= widgetID)
        return -1; //widget does not exist.

    ILayer *newLayer = CWidgetFactory::getLayer(layerType, args);
    if (newLayer == NULL)
        return -1; //not found in factory.

    m_itsWidgets[widgetID].push_back(newLayer);
    return m_itsWidgets[widgetID].size() - 1;
}

bool CCanvas::UpdateWidget(int widgetID)
{
    if (m_itsWidgets.size() <= widgetID)
        return false;

    CRect<int> drawArea = m_widgetAreas[widgetID];
    CPoint<int> topLeft(0, 0);
    CBuffer<CRGB> drawBuffer(m_itsCanvas, drawArea);
    for (int j = 0; j < m_itsWidgets[widgetID].size(); ++j)
    {
        ILayer *currentLayer = m_itsWidgets[widgetID][j];
        currentLayer->setData(&m_itsData[widgetID]);
        currentLayer->setTextProperties(&m_widgetTexts[widgetID]);
        drawArea += topLeft;
        currentLayer->Draw(drawBuffer);
        drawArea = currentLayer->getActiveArea();
        if (drawArea.getHeigth() <= 0 || drawArea.getWidth() <= 0)
        {
            break;
        }
        topLeft = topLeft + drawArea.getTopLeft();
        drawBuffer = CBuffer<CRGB>(drawBuffer, drawArea);
        int w = drawArea.getWidth();
        int h = drawArea.getHeigth();

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

bool CCanvas::setxAxisLabel(int widgetID, const char *labelText)
{
    if (m_widgetTexts.size() <= widgetID)
        return false;

    m_widgetTexts[widgetID].xAxisText.setText(labelText);
    return true;
}

bool CCanvas::setyAxisLabel(int widgetID, const char *labelText)
{
    if (m_widgetTexts.size() <= widgetID)
        return false;

    m_widgetTexts[widgetID].yAxisText.setText(labelText);
    return true;
}

bool CCanvas::setDataName(int widgetID, int dataID, const char *name)
{
    if (m_itsWidgets.size() <= widgetID)
        return false;

    if (m_itsData[widgetID].size() <= dataID)
        return false;

    m_itsData[widgetID][dataID]->setName(name);
    return true;
}

bool CCanvas::setDataColor(int widgetID, int dataID, CRGB color)
{
    if (m_itsWidgets.size() <= widgetID)
        return false;

    if (m_itsData[widgetID].size() <= dataID)
        return false;

    m_itsData[widgetID][dataID]->color = color;
    return true;
}

bool CCanvas::setWidgetBackgroundColor(int widgetID, CRGB color)
{
    if (m_itsWidgets.size() <= widgetID)
        return false;
    m_widgetBgColors[widgetID] = color;

    for (int i = 0; i < m_itsWidgets[widgetID].size(); ++i)
        m_itsWidgets[widgetID][i]->setBackgroundColor(color);

    return true;
}

bool CCanvas::ExecuteSpecialLayerCmd(int widgetID, int layerID, void *command, void *args)
{
    if (m_itsWidgets.size() <= widgetID)
        return false;

    if (m_itsWidgets[widgetID].size() <= layerID)
        return false;

    m_itsWidgets[widgetID][layerID]->SpecialCommand(command, args);
    return true;
}

void CCanvas::MouseMove(int x, int y)
{
    //std::cout << x << '@' << y << std::endl;
    for (int i = 0; i < m_widgetAreas.size(); ++i)
    {
        if (m_widgetAreas[i].IsIn(CPoint<int>(x, y)))
        {
            //std::cout << "Mouse over widget " << i << std::endl;
            bool needRedraw = false;
            CPoint<int> layerPos = m_widgetAreas[i].getTopLeft();
            for (int j = 0; j < m_itsWidgets[i].size(); ++j)
            {
                needRedraw |= m_itsWidgets[i][j]->MouseMove(x - layerPos.x, y - layerPos.y);
            }
            if (needRedraw)
            {
                UpdateWidget(i);
            }
            break;
        }
    }
}
void CCanvas::KeyPress(unsigned char key, bool pressed)
{
    //std::cout << "KeyPress:" << (int)key << pressed << std::endl;
    CPoint<int> mousePos = m_itsDisplay.getLastMousePos();
    for (int i = 0; i < m_widgetAreas.size(); ++i)
    {
        if (m_widgetAreas[i].IsIn(mousePos))
        {
            bool needRedraw = false;
            for (int j = 0; j < m_itsWidgets[i].size(); ++j)
            {
                needRedraw |= m_itsWidgets[i][j]->KeyPress(key, true);
            }
            if (needRedraw)
            {
                UpdateWidget(i);
            }
            break;
        }
    }
}
void CCanvas::MousePress(int x, int y, unsigned char key, bool pressed)
{
}