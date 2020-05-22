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
	int clockWidget = myCanvas.CreateWidget("AnalogClock", CRect<int>(10, 10, 210, 210));
	int clockWidget2 = myCanvas.CreateWidget("AnalogClock", CRect<int>(10, 310, 410, 610));
	myCanvas.setWidgetTitle(clockWidget, "NICE CLOCK");
	float timeData[] = {18, 32, 0};
	int timeDataID = myCanvas.InsertData(clockWidget, timeData, timeData + 3);
	int timeDataID2 = myCanvas.InsertData(clockWidget2, timeData, timeData + 3);
	while (true)
	{
		timeData[2] += 1;
		myCanvas.ReplaceData(clockWidget, timeDataID, timeData, timeData + 3);
		myCanvas.UpdateWidget(clockWidget);
		myCanvas.ReplaceData(clockWidget2, timeDataID2, timeData, timeData + 3);
		myCanvas.UpdateWidget(clockWidget2);
		printf("a\n");
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