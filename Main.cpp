#include <iostream>
#include "CCanvas.h"
#include "DrawUtils.h"

#include <math.h>
#include <vector>
#include <list>
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
	pieData = 30;
	myCanvas.InsertData(pieWidget, &pieData, &pieData + 1);
	pieData = 20;
	myCanvas.InsertData(pieWidget, &pieData, &pieData + 1);
	pieData = 40;
	myCanvas.InsertData(pieWidget, &pieData, &pieData + 1);

	//A bar graph widget
	int barWidget = myCanvas.CreateWidget(CRect<int>(420, 320, 640, 610));
	myCanvas.InsertLayer(barWidget, "BackgroundManager");
	myCanvas.InsertLayer(barWidget, "2dAxisHandler");
	int barLayer = myCanvas.InsertLayer(barWidget, "BarGraph");
	myCanvas.InsertLayer(barWidget, "LegendHandler");
	myCanvas.setWidgetTitle(barWidget, "BAR GRAPH");
	myCanvas.setxAxisLabel(barWidget, "X AXIS");
	myCanvas.setyAxisLabel(barWidget, "Y AXIS");

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
	int timeDataHour = myCanvas.InsertData(clockWidget, &data, &data + 1);
	data = 30;
	int timeDataMin = myCanvas.InsertData(clockWidget, &data, &data + 1);
	data = 45;
	int timeDataSec = myCanvas.InsertData(clockWidget, &data, &data + 1);
	//Paint hour and minute hands to black, second hand to red
	myCanvas.setDataColor(clockWidget, timeDataHour, CRGB(0,0,0));
	myCanvas.setDataColor(clockWidget, timeDataMin, CRGB(0,0,0));
	myCanvas.setDataColor(clockWidget, timeDataSec, CRGB(255,0,0));

	//Insert 2 data to line graph, a sine wave and a cosine wave
	std::list<int> sinx, siny;
	for (int i = 0; i < 720; i += 10)
	{
		sinx.push_back(i);
		float radX = float(i) * 3.14f / 180;
		float sinVal = sin(radX);
		int y = ROUND(sinVal * 50 + 100);
		siny.push_back(y);
	}
	int sinLine = myCanvas.InsertData(lineGraphWidget, siny.begin(), siny.end());
	myCanvas.setDataName(lineGraphWidget, sinLine, "SINE WAVE");
	std::list<int> cosx, cosy;
	for (int i = 0; i < 720; i += 10)
	{
		cosx.push_back(i);
		float radX = float(i) * 3.14f / 180;
		float sinVal = cos(radX);
		int y = ROUND(sinVal * 50 + 100);
		cosy.push_back(y);
	}
	int cosLine = myCanvas.InsertData(lineGraphWidget, cosy.begin(), cosy.end());
	myCanvas.setDataName(lineGraphWidget, cosLine, "COS WAWE");

	//updating widgets triggers a redraw for all.
	//if display is enabled, it is updated as well.
	myCanvas.UpdateAllWidgets();

	while (true)
	{
		//increment clock's second by 1.
		data += 1;
		myCanvas.ReplaceData(clockWidget, timeDataSec, &data, &data + 1);
		myCanvas.UpdateWidget(clockWidget);

		//shift sin and cos lines
		siny.push_front(siny.back());
		siny.pop_back();
		myCanvas.ReplaceData(lineGraphWidget, sinLine, siny.begin(), siny.end());

		cosy.push_back(cosy.front());
		cosy.pop_front();
		myCanvas.ReplaceData(lineGraphWidget, cosLine, cosy.begin(), cosy.end());
		myCanvas.UpdateWidget(lineGraphWidget);
		usleep(1000*100);
	}
	return 0;
}