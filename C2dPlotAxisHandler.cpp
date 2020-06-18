#include "C2dPlotAxisHandler.h"
#include "DrawUtils.h"

void C2dPlotAxisHandler::setTextProperties(WidgetTextFields *texts)
{
    m_texts = texts;
}

void C2dPlotAxisHandler::setData(std::vector<CSeriesData *> *data)
{
    m_data = data;
}

CRect<int> C2dPlotAxisHandler::getActiveArea()
{
    return m_activeArea;
}

void C2dPlotAxisHandler::Draw(CBuffer<CRGB> buf)
{
    buf.Fill(CRGB(255, 255, 0));
    m_activeArea = buf.getAreaRect();

    if (m_texts->xAxisText.getText() != NULL)
    {
        CPoint<int> textSize = DrawUtils<CRGB>::getStringSize(m_texts->xAxisText.getText());
        if (!m_texts->xAxisText.isPosSetExt)
        {
            m_texts->xAxisText.pos.X() = (buf.getWidth() - textSize.X()) / 2;
            m_texts->xAxisText.pos.Y() = m_activeArea.getBottom() - textSize.Y() - 1;
            DrawUtils<CRGB>::DrawString(buf, m_texts->xAxisText.color, m_texts->xAxisText.pos, m_texts->xAxisText.getText());
            m_activeArea.ShiftBottom(-textSize.Y() - 1);
        }
    }

    if (m_texts->yAxisText.getText() != NULL)
    {
        CPoint<int> textSize = DrawUtils<CRGB>::getStringSize(m_texts->yAxisText.getText());
        if (!m_texts->yAxisText.isPosSetExt)
        {
            m_texts->yAxisText.pos.Y() = (buf.getHeigth() + textSize.X()) / 2;
            m_texts->yAxisText.pos.X() = m_activeArea.getLeft() + 1;
            DrawUtils<CRGB>::DrawStringRotatedLeft(buf, m_texts->yAxisText.color, m_texts->yAxisText.pos, m_texts->yAxisText.getText());
            m_activeArea.ShiftLeft(textSize.Y() + 1);
        }
    }
    DrawUtils<CRGB>::DrawRectangle(buf, CRGB(0,0,0), m_activeArea);
}
