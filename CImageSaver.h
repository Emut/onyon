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
	static bool ReadFromPpm(CBuffer<T> *&buf, const std::string fileNameStr)
	{
		const char *fileName = fileNameStr.c_str();
		FILE *filep = NULL;
		filep = fopen(fileName, "rb");
		if (filep == NULL)
			return false;
		char temp[2];
		fread(temp, 1, 2, filep);
		//check header
		if (temp[0] != 'P' || temp[1] != '6')
		{
			//file format is wrong
			fclose(filep);
			return false;
		}

		char readVal = 0;
		//array to hold width heigth and depth
		int whd[3];
		for(int i = 0; i < 4; ++i)
		{
		//consume all whitespace
		while (true)
		{
			fread(&readVal, 1, 1, filep);
			if (readVal == ' ' || readVal == '\n' || readVal == '\r' || readVal == '\t')
			{
				continue;
			}
			//go back once to point beginning of ascii num
			fseek(filep, -1, SEEK_CUR);
			break;
		}
		if(i == 3)
			break;
			
		fscanf(filep, "%d", whd+i);
		}

		buf = new CBuffer<T>(whd[0], whd[1]);

		for(int row = 0; row < whd[1]; ++row){
			for(int col = 0; col < whd[0]; ++col){
				T readPixel;
				unsigned char readVal;
				fread(&readVal, 1, 1, filep);
				readPixel.setRed(readVal);
				fread(&readVal, 1, 1, filep);
				readPixel.setGreen(readVal);
				fread(&readVal, 1, 1, filep);
				readPixel.setBlue(readVal);
				buf->getElmRef(col, row) = readPixel;
			}
		}
		
		fclose(filep);
		return true;
	}
};