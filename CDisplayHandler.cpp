#include "CDisplayHandler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CDisplayHandler::CDisplayHandler(int windowWidth, int windowHeigth, const char *windowName)
{
    int nameLength = strlen(windowName);
    m_windowName = new char[nameLength + 1];
    strcpy(m_windowName, windowName);
    namedWindow(windowName, WINDOW_AUTOSIZE);
    setMouseCallback(windowName, MouseMoveCallback);
}

CDisplayHandler::~CDisplayHandler()
{
}

bool CDisplayHandler::Update(CBuffer<CRGB>& image)
{
    Mat temp = Mat(image.getHeigth(), image.getWidth(), CV_8UC3, image.getBufferPointer());
    imshow(m_windowName, temp);
    waitKey(25);
    return true;
}

void CDisplayHandler::MouseMoveCallback(int event, int x, int y, int flag, void *param){
    cout<<x<<' '<<y<<endl;
}