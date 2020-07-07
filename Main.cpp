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

	//create a canvas and enable display window
	CCanvas myCanvas(640, 680);
	myCanvas.DisplayOnScreen(true, "myWindow");

	//A clock wiget with a picture of an onion as background
	int clockWidget = myCanvas.CreateWidget(CRect<int>(10, 10, 210, 210));
	myCanvas.InsertLayer(clockWidget, "BackgroundManager", "onion.ppm");
	int clockLayer = myCanvas.InsertLayer(clockWidget, "AnalogClock");
	myCanvas.setWidgetTitle(clockWidget, "NICE CLOCK");

	//A line graph with a 2d Axis and a legend on top
	int lineGraphWidget = myCanvas.CreateWidget(CRect<int>(10, 220, 410, 610));
	myCanvas.InsertLayer(lineGraphWidget, "BackgroundManager");
	myCanvas.InsertLayer(lineGraphWidget, "2dAxisHandler");
	int lineGraphLayer = myCanvas.InsertLayer(lineGraphWidget, "LineGraph");
	myCanvas.InsertLayer(lineGraphWidget, "LegendHandler");
	myCanvas.setWidgetTitle(lineGraphWidget, "LINE GRAPH");
	myCanvas.setxAxisLabel(lineGraphWidget, "X AXIS LABEL");
	myCanvas.setyAxisLabel(lineGraphWidget, "Y AXIS LABEL");

	//A widget to demonstrate mouse and keyboard inputs
	int mkWidget = myCanvas.CreateWidget(CRect<int>(220, 10, 410, 210));
	myCanvas.InsertLayer(mkWidget, "BackgroundManager", "onion.ppm");
	myCanvas.InsertLayer(mkWidget, "MouseKeyboardSample");

	//A pie chart widget
	int pieWidget = myCanvas.CreateWidget(CRect<int>(420, 10, 640, 310));
	myCanvas.InsertLayer(pieWidget, "BackgroundManager");
	int pieLayer = myCanvas.InsertLayer(pieWidget, "PieChartLayer");
	myCanvas.InsertLayer(pieWidget, "LegendHandler");
	myCanvas.setWidgetTitle(pieWidget, "PIE CHART");
	int pieData = 80;
	myCanvas.InsertData(pieWidget, &pieData, &pieData + 1);
	pieData = 20;
	myCanvas.InsertData(pieWidget, &pieData, &pieData + 1);

	//A bar graph widget
	int barWidget = myCanvas.CreateWidget(CRect<int>(420, 320, 640, 610));
	myCanvas.InsertLayer(barWidget, "BackgroundManager");
	// int pieLayer = myCanvas.InsertLayer(lineGraphWidget, "LineGraph");
	myCanvas.InsertLayer(barWidget, "LegendHandler");
	myCanvas.setWidgetTitle(barWidget, "BAR GRAPH");

	//Use specialCmd command to set clock's dial and number colors to black
	CRGB arg = CRGB(0, 0, 0);
	int cmd = 0;
	myCanvas.ExecuteSpecialLayerCmd(clockWidget, clockLayer, &cmd, &arg);
	cmd = 1;
	myCanvas.ExecuteSpecialLayerCmd(clockWidget, clockLayer, &cmd, &arg);
	cmd = 2;
	myCanvas.ExecuteSpecialLayerCmd(clockWidget, clockLayer, &cmd, &arg);

	//set the time for clock. Order is hour, minute and second.
	//save the dataId of second to manipulate later
	float data = 10;
	myCanvas.InsertData(clockWidget, &data, &data + 1);
	data = 30;
	myCanvas.InsertData(clockWidget, &data, &data + 1);
	data = 45;
	int timeDataSec1 = myCanvas.InsertData(clockWidget, &data, &data + 1);

	//Insert 2 data to line graph, a sine wave and a cosine wave
	std::vector<int> vectx, vecty;
	for (int i = 0; i < 600; i += 10)
	{
		vectx.push_back(i);
		float radX = float(i) * 3.14f / 180;
		float sinVal = sin(radX);
		int y = ROUND(-sinVal * 50 + 100);
		vecty.push_back(y);
	}
	int sinLine = myCanvas.InsertData(lineGraphWidget, vecty.begin(), vecty.end());
	myCanvas.setDataName(lineGraphWidget, sinLine, "SINE WAVE");
	vecty.clear();
	vectx.clear();
	for (int i = 0; i < 600; i += 20)
	{
		vectx.push_back(i);
		float radX = float(i) * 3.14f / 180;
		float sinVal = cos(radX);
		int y = ROUND(-sinVal * 50 + 100);
		vecty.push_back(y);
	}
	int cosLine = myCanvas.InsertData(lineGraphWidget, vecty.begin(), vecty.end());
	myCanvas.setDataName(lineGraphWidget, cosLine, "COS WAWE");

	//updating widgets triggers a redraw for all.
	//if display is enabled, it is updated as well.
	myCanvas.UpdateAllWidgets();

	while (true)
	{
		data += 1;
		myCanvas.ReplaceData(clockWidget, timeDataSec1, &data, &data + 1);
		myCanvas.UpdateWidget(clockWidget);
		sleep(1);
	}
	myCanvas.SaveAsPpm("asd.pgm");

	std::cin >> c;
	return 0;

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