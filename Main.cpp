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
	myCanvas.InsertLayer(clockWidget, "BackgroundManager", "onion.ppm");
	myCanvas.InsertLayer(clockWidget, "AnalogClock");

	int clockWidget2 = myCanvas.CreateWidget(CRect<int>(10, 220, 410, 610));
	myCanvas.InsertLayer(clockWidget2, "BackgroundManager", "onion.ppm");
	myCanvas.InsertLayer(clockWidget2, "2dAxisHandler");
	int clockLayer = myCanvas.InsertLayer(clockWidget2, "LineGraph");

	int mkWidget = myCanvas.CreateWidget(CRect<int>(220, 10, 410, 210));
	myCanvas.InsertLayer(mkWidget, "BackgroundManager", "onion.ppm");
	myCanvas.InsertLayer(mkWidget, "MouseKeyboardSample");

	myCanvas.setWidgetTitle(clockWidget, "NICE CLOCK");
	myCanvas.setWidgetTitle(clockWidget2, "LINE GRAPH");
	myCanvas.setxAxisLabel(clockWidget2, "X AXIS LABEL");
	myCanvas.setyAxisLabel(clockWidget2, "Y AXIS LABEL");

	myCanvas.UpdateAllWidgets();

	int cmd = 0;
	CRGB arg = CRGB(255, 255, 255);
	myCanvas.ExecuteSpecialLayerCmd(clockWidget2, clockLayer, &cmd, &arg);
	cmd = 1;
	myCanvas.ExecuteSpecialLayerCmd(clockWidget2, clockLayer, &cmd, &arg);
	cmd = 2;
	myCanvas.ExecuteSpecialLayerCmd(clockWidget2, clockLayer, &cmd, &arg);

	float data = 10;
	myCanvas.InsertData(clockWidget, &data, &data + 1);
	data = 16;
	//myCanvas.InsertData(clockWidget2, &data, &data + 1);
	data = 30;
	myCanvas.InsertData(clockWidget, &data, &data + 1);
	//myCanvas.InsertData(clockWidget2, &data, &data + 1);
	data = 45;
	int timeDataSec1 = myCanvas.InsertData(clockWidget, &data, &data + 1);
	//int timeDataSec2 = myCanvas.InsertData(clockWidget2, &data, &data + 1);
	std::vector<int> vectx, vecty;
	for (int i = 0; i < 600; i += 20)
	{
		vectx.push_back(i);
		float radX = float(i) * 3.14f / 180;
		float sinVal = cos(radX);
		int y = ROUND(-sinVal * 50 + 100);
		vecty.push_back(y);
	}
	myCanvas.InsertData(clockWidget2, vecty.begin(), vecty.end());
	//myCanvas.setDataColor(clockWidget2, timeDataSec2, CRGB(255, 255, 255));
	//myCanvas.setWidgetBackgroundColor(clockWidget2, CRGB(0, 0, 0));
	//int timeDataID2 = myCanvas.InsertData(clockWidget2, timeData, timeData + 3);
	while (true)
	{
		data += 1;
		myCanvas.ReplaceData(clockWidget, timeDataSec1, &data, &data + 1);
	//	myCanvas.ReplaceData(clockWidget2, timeDataSec2, &data, &data + 1);
		myCanvas.UpdateWidget(clockWidget);
		myCanvas.UpdateWidget(clockWidget2);
		sleep(1);
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

	int heartDataCount = 2 * 3.1415 / 0.01;
	float *heartX = new float[heartDataCount];
	float *heartY = new float[heartDataCount];
	for (int i = 0; i < heartDataCount; i += 1)
	{
		float step = i * 0.01;
		heartX[i] = (16 * pow(sin(step), 3));
		float temp = 0;
		temp += 13 * cos(step);
		temp -= 5 * cos(2 * step);
		temp -= 2 * cos(3 * step);
		temp -= cos(4 * step);
		heartY[i] = (-temp);
	}
}