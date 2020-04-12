#include "CDisplayHandler.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

CDisplayHandler::CDisplayHandler(int windowWidth, int windowHeigth, const char *windowName)
{
    namedWindow("Display window", WINDOW_AUTOSIZE);
}

CDisplayHandler::~CDisplayHandler()
{
}

bool CDisplayHandler::Update(CBuffer<CRGB>& image)
{
    Mat temp = Mat(image.getHeigth(), image.getWidth(), CV_8UC3, image.getBufferPointer());
    imshow("Display window", temp);
    waitKey();
    return true;
}