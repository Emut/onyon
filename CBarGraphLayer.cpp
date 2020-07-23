#include "CBarGraphLayer.h"

void CBarGraphLayer::Draw(CBuffer<CRGB> buf)
{
    m_activeArea = buf.getAreaRect();
    buf.Fill(CRGB(0,0,128));
}

void CBarGraphLayer::setData(std::vector<CSeriesData *> *data){
    m_data = data;
}

CRect<int> CBarGraphLayer::getActiveArea(){
    return m_activeArea;
}