#include "CBuffer.h"
#include <stdio.h>
#include <string>
#include <string.h>

class CImageSaver
{
public:
	template <class T>
	static bool SaveAsPgm(CBuffer<T> &image, const char *fileName)
	{
		FILE *filep = NULL;
		filep = fopen(fileName, "wb");
		if (filep == NULL)
			return false;

		fwrite("P5\n", 1, 3, filep);
		int width = image.getWidth();
		int heigth = image.getHeigth();

		fprintf(filep, "%d\n%d\n255\n", width, heigth);

		for (int j = 0; j < heigth; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				unsigned char grayVal = image.getElmRef(i, j).getGray();
				fwrite(&grayVal, 1, 1, filep);
			}
		}

		fclose(filep);
		return true;
	}

	template <class T>
	static bool SaveAsPpm(CBuffer<T> &image, const char *fileName)
	{
		FILE *filep = NULL;
		filep = fopen(fileName, "wb");
		if (filep == NULL)
			return false;

		fwrite("P6\n", 1, 3, filep);
		int width = image.getWidth();
		int heigth = image.getHeigth();

		fprintf(filep, "%d\n%d\n255\n", width, heigth);

		for (int j = 0; j < heigth; ++j)
		{
			for (int i = 0; i < width; ++i)
			{
				T readVal = image.getElmRef(i, j);
				unsigned char rgb[3];
				rgb[0] = readVal.getRed();
				rgb[1] = readVal.getGreen();
				rgb[2] = readVal.getBlue();
				fwrite(rgb, 1, 3, filep);
			}
		}

		fclose(filep);
		return true;
	}

	template <class T>
	static bool ReadFromPpm(CBuffer<T>* buf, const std::string fileNameStr)
	{
		const char* fileName = fileNameStr.c_str();
		FILE *filep = NULL;
		filep = fopen(fileName, "rb");
		if (filep == NULL)
			return false;
		char temp[5];
		fread(temp, 1, 3, filep);
		if(strcmp(temp, "P6") != 0){
			//file format is wrong
			fclose(filep);
			return false;
		}
		int width = 0;
		int heigth = 0;
		int depth = 0;

		int read = fscanf(filep, "%d\n%d\n%d\n", &width, &heigth, &depth);
		if(read != 3){
			fclose(filep);
			return false;
		}
		fprintf(filep, "%d,%d,%d", width, heigth, depth);
		fclose(filep);
		return false;
	}
};