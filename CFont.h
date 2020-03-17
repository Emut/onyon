#ifndef CFONT_H
#define CFONT_H

template <class T>
struct tsPoint{
	T X;
	T Y;
	tsPoint(T x, T y): X(x), Y(y){}
};

struct tsLetterGlyph{
	unsigned char width;
	unsigned char heigth;

	int corePxCnt;
	int outlinePxCnt;

	tsPoint<unsigned char>* corePxs;
	tsPoint<unsigned char>* outlinePxs;

	//tsLetterGlyph(unsigned char w, unsigned char h): 
};

class IFont{
public:
	tsLetterGlyph itsLetters[256];
	virtual tsLetterGlyph* getLetter(unsigned char letter) = 0;
};
#endif