#include "CDisplayHandler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CDisplayHandler* CDisplayHandler::theInstance = NULL;

CDisplayHandler::CDisplayHandler(int windowWidth, int windowHeigth, const char *windowName, IDisplayOwner* owner): m_mousePos(0,0)
{
    m_owner = owner;
    int nameLength = strlen(windowName);
    m_windowName = new char[nameLength + 1];
    strcpy(m_windowName, windowName);
    namedWindow(windowName, WINDOW_AUTOSIZE);
    setMouseCallback(windowName, MouseMoveCallback);
    
    theInstance = this;
}

CDisplayHandler::~CDisplayHandler()
{
}

bool CDisplayHandler::Update(CBuffer<CRGB>& image)
{
    Mat temp = Mat(image.getHeigth(), image.getWidth(), CV_8UC3, image.getBufferPointer());
    imshow(m_windowName, temp);
    int key = waitKey(1);
    if(key >= 0 && key < 255){
        //std::cout<<"key:"<<key<<std::endl;
        if(m_owner != NULL)
            m_owner->KeyPress(key, true);
    }

    return true;
}

void CDisplayHandler::MouseMoveCallback(int event, int x, int y, int flag, void *param){
    //cout<<x<<' '<<y<<endl;
    theInstance->m_mousePos = CPoint<int>(x,y);
    if(theInstance->m_owner != NULL)
        theInstance->m_owner->MouseMove(x, y);
}

CPoint<int> CDisplayHandler::getLastMousePos(){
    return m_mousePos;
}