#include "CBuffer.h"
#include <stdio.h>


class CImageSaver{
public:
	template<class T>
	static bool SaveAsPgm(CBuffer<T>& image, const char* fileName){
		FILE* filep = NULL;
		filep = fopen(fileName, "wb");
		if(filep == NULL)
			return false;


		fwrite("P5\n", 1, 3, filep);
		int width = image.getWidth();
		int heigth = image.getHeigth();

		fprintf(filep, "%d\n%d\n255\n", width, heigth); 

		for(int j = 0; j < heigth; ++j){
			for(int i = 0; i < width; ++i){
				unsigned char grayVal = image.getElmRef(i, j).getGray(); 
				fwrite(&grayVal, 1, 1, filep);
			}
		}

		fclose(filep);
		return true;
	}

	template<class T>
	static bool SaveAsPpm(CBuffer<T>& image, const char* fileName){
		FILE* filep = NULL;
		filep = fopen(fileName, "wb");
		if(filep == NULL)
			return false;


		fwrite("P6\n", 1, 3, filep);
		int width = image.getWidth();
		int heigth = image.getHeigth();

		fprintf(filep, "%d\n%d\n255\n", width, heigth); 

		for(int j = 0; j < heigth; ++j){
			for(int i = 0; i < width; ++i){
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

};