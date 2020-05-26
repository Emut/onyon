#include <iostream>
//#include "CBuffer.h"
//#include "DrawUtils.h"
//#include "CImageSaver.h"
#include "CPlotter.h"
#include "CCanvas.h"

#include <math.h>
#include <vector>
#include <unistd.h>

int main()
{
	char c;

	std::cout << "Hi" << std::endl;

	CCanvas myCanvas(640, 480);
	myCanvas.DisplayOnScreen(true, "myWindow");
	int clockWidget = myCanvas.CreateWidget(CRect<int>(10, 10, 210, 210));
	myCanvas.InsertLayer(clockWidget, "BackgroundManager");
	myCanvas.InsertLayer(clockWidget, "AnalogClock");
	
	
	int clockWidget2 = myCanvas.CreateWidget(CRect<int>(10, 220, 410, 610));
	myCanvas.InsertLayer(clockWidget2, "BackgroundManager");
	int clockLayer = myCanvas.InsertLayer(clockWidget2, "AnalogClock");

	int mkWidget = myCanvas.CreateWidget(CRect<int>(220, 10, 410, 210));
	myCanvas.InsertLayer(mkWidget, "BackgroundManager", "image.ppm");
	myCanvas.InsertLayer(mkWidget, "MouseKeyboardSample");

	myCanvas.setWidgetTitle(clockWidget, "NICE CLOCK");
	myCanvas.setWidgetTitle(clockWidget2, "HUGE CLOCK");

	myCanvas.UpdateAllWidgets();
	
	int cmd = 0;
	CRGB arg = CRGB(255,255,255);
	myCanvas.ExecuteSpecialLayerCmd(clockWidget2, clockLayer, &cmd, &arg);
	cmd = 1;
	myCanvas.ExecuteSpecialLayerCmd(clockWidget2, clockLayer, &cmd, &arg);
	cmd = 2;
	myCanvas.ExecuteSpecialLayerCmd(clockWidget2, clockLayer, &cmd, &arg);

	float data = 10;
	myCanvas.InsertData(clockWidget, &data, &data + 1);
	data = 16;
	myCanvas.InsertData(clockWidget2, &data, &data + 1);
	data = 30;
	myCanvas.InsertData(clockWidget, &data, &data + 1);
	myCanvas.InsertData(clockWidget2, &data, &data + 1);
	data = 45;
	int timeDataSec1 = myCanvas.InsertData(clockWidget, &data, &data + 1);
	int timeDataSec2 = myCanvas.InsertData(clockWidget2, &data, &data + 1);
	myCanvas.setDataColor(clockWidget2,timeDataSec2,CRGB(255,255,255));
	myCanvas.setWidgetBackgroundColor(clockWidget2,CRGB(0,0,0));
	//int timeDataID2 = myCanvas.InsertData(clockWidget2, timeData, timeData + 3);
	while (true)
	{
		data += 1;
		myCanvas.ReplaceData(clockWidget, timeDataSec1, &data, &data + 1);
		myCanvas.ReplaceData(clockWidget2, timeDataSec2, &data, &data + 1);
		myCanvas.UpdateWidget(clockWidget);
		myCanvas.UpdateWidget(clockWidget2);
		//printf("a\n");
		//std::cin >> c;
		//sleep(1);
	}
	myCanvas.SaveAsPpm("asd.pgm");

	std::cin >> c;
	return 0;

	CPlotter myPlot;
	myPlot.setTitle("0123456789 ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	myPlot.ToggleDisplayWindow(true);
	std::vector<int> vectx, vecty;
	for (int i = 0; i < 600; i += 20)
	{
		vectx.push_back(i);
		float radX = float(i) * 3.14f / 180;
		float sinVal = cos(radX);
		int y = ROUND(-sinVal * 50 + 100);
		vecty.push_back(y);
	}

	std::vector<float> heartX;
	std::vector<float> heartY;
	for (float i = 0; i < 2 * 3.1415; i += 0.01)
	{
		heartX.push_back(16 * pow(sin(i), 3));
		float temp = 0;
		temp += 13 * cos(i);
		temp -= 5 * cos(2 * i);
		temp -= 2 * cos(3 * i);
		temp -= cos(4 * i);
		heartY.push_back(-temp);
	}
	int heartLine = myPlot.Plot(heartY.begin(), heartY.end(), heartX.begin(), heartX.end());
	myPlot.setLineColor(heartLine, CRGB(255, 0, 0));
	myPlot.SaveAsPpm("heart.ppm");
	int shortSine = myPlot.Plot(vecty.begin(), vecty.end());
	myPlot.setLineDataPointMarker(shortSine, LineData::DPM_CIRCLE);
	//myPlot.SaveAsPpm("image1.ppm");
	myPlot.Plot(vecty.begin(), vecty.end(), vectx.begin(), vectx.end());
	//myPlot.SaveAsPpm("image2.ppm");

	//myPlot.SaveAsPpm("image3.ppm");
	myPlot.setX_AxisLabel("X LABEL");
	//myPlot.SaveAsPpm("image4.ppm");
	myPlot.setY_AxisLabel("Y LABEL");

	myPlot.SaveAsPgm("image.pgm");
	myPlot.SaveAsPpm("image.ppm");

	return 0;
}