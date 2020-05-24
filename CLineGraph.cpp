#include "CLineGraph.h"

CLineGraph::CLineGraph(): m_itsCanvas(0,0){}

void CLineGraph::Create(CBuffer<CRGB> itsCanvas){
    m_itsCanvas = itsCanvas;
    //m_itsBgManager.Create(m_itsCanvas);
}
void CLineGraph::Draw(const std::vector<CSeriesData*>& data){
    //m_itsCanvas.Fill(CRGB(255,0,0));
}