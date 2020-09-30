# onyon :onion:

Because if I have to launch MATLAB once more, I will end myself ™ 

A C++98 compatible extensible data visualisation framework. 
* Create dynamic widgets by combining image producing layers (Backgrounds, axis handlers, legends, plotters etc.) on top of each other.
* Place multiple widgets on the canvas to display multiple data in different ways.
* Save resulting image as file. (Only .ppm support at the moment)
* Can display image in a window, (Requires OpenCV support at the moment)
* Capture mouse movement and keyboard presses to use in visualization.
* Platform independent and C++98 code should compile with anything made in the last two decades. (Apart from the display window isolated to a single class)

## Getting Started

A sample. Code can be found below and in main.cpp file.

What will it look like (Don't worry, colors and resolution are better than the GIF below :)
![Peek 2020-09-30 17-53](https://user-images.githubusercontent.com/42119171/94702243-3400e500-0346-11eb-9858-5d1225ce9367.gif)

The code:
```c++
//create a canvas and enable display window
CCanvas myCanvas(640, 880);
myCanvas.DisplayOnScreen(true, "myWindow");

//A clock widget with a picture of an onion as background
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
float barData = 20;
myCanvas.InsertData(barWidget, &barData, &barData + 1);
barData = 30;
myCanvas.InsertData(barWidget, &barData, &barData + 1);
barData = 40;
myCanvas.InsertData(barWidget, &barData, &barData + 1);
barData = 25;
myCanvas.InsertData(barWidget, &barData, &barData + 1);
barData = 10;
myCanvas.InsertData(barWidget, &barData, &barData + 1);

//A horizontal bar graph widget
int horBarWidget = myCanvas.CreateWidget(CRect<int>(650, 10, 870, 610));
myCanvas.InsertLayer(horBarWidget, "BackgroundManager");
myCanvas.InsertLayer(horBarWidget, "2dAxisHandler");
int horBarLayer = myCanvas.InsertLayer(horBarWidget, "HorizontalBarGraph");
myCanvas.InsertLayer(horBarWidget, "LegendHandler");
myCanvas.setWidgetTitle(horBarWidget, "BAR GRAPH");
myCanvas.setxAxisLabel(horBarWidget, "X AXIS");
myCanvas.setyAxisLabel(horBarWidget, "Y AXIS");
float horBarData = 20;
myCanvas.InsertData(horBarWidget, &horBarData, &horBarData + 1);
horBarData = 10;
myCanvas.InsertData(horBarWidget, &horBarData, &horBarData + 1);
horBarData = 50;
myCanvas.InsertData(horBarWidget, &horBarData, &horBarData + 1);
horBarData = -10;
myCanvas.InsertData(horBarWidget, &horBarData, &horBarData + 1);
horBarData = 10;
myCanvas.InsertData(horBarWidget, &horBarData, &horBarData + 1);

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
```

To build the sample on linux: ```g++ *.cpp -lopencv_highgui -lopencv_core -I/usr/include/opencv4```

to install opencv on linux: ```sudo apt-get install libopencv-dev```

## What is missing
* More layers to create more widgets!
* Platform dependent window handling to get rid of OpenCV dependency.
* Data binding to layers, so multiple layers can use different sets of data in a single widget to draw on top of each other (e.g. a bar and a line graph)
* General control interfaces for more customizability (e.g. place legend at a specific position, change text color etc.)
* Image exporting to more useful formats (e.g. jpeg, png)
