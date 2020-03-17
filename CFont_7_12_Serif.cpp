#include "CFont_7_12_Serif.h"

unsigned char defGlyph[] = {1,3,2,3,3,3,4,3,5,3,
							1,4,5,4,
							1,5,5,5,
							1,6,5,6,
							1,7,5,7,
							1,8,5,8,
							1,9,2,9,3,9,4,9,5,9}; 

unsigned char num0[] = {2,3,3,3,4,3,
						1,4,5,4,
						1,5,5,5,
						1,6,5,6,
						1,7,5,7,
						1,8,5,8,
						2,9,3,9,4,9}; 

unsigned char num1[] = {3,3,
						1,4,2,4,3,4,
						3,5,
						3,6,
						3,7,
						3,8,
						1,9,2,9,3,9,4,9,5,9}; 

unsigned char num2[] = {2,3,3,3,4,3,
						1,4,5,4,
						5,5,
						3,6,4,6,
						2,7,
						1,8,5,8,
						1,9,2,9,3,9,4,9,5,9}; 

unsigned char num3[] = {2,3,3,3,4,3,
						1,4,5,4,
						5,5,
						3,6,4,6,
						5,7,
						1,8,5,8,
						2,9,3,9,4,9}; 

unsigned char num4[] = {2,3,4,3,
						2,4,4,4,
						1,5,4,5,
						1,6,4,6,
						1,7,2,7,3,7,4,7,5,7,
						4,8,
						3,9,4,9,5,9}; 

unsigned char num5[] = {1,3,2,3,3,3,4,3,5,3,
						1,4,
						1,5,2,5,3,5,4,5,
						5,6,
						5,7,
						1,8,5,8,
						2,9,3,9,4,9}; 

unsigned char num6[] = {2,3,3,3,4,3,
						1,4,5,4,
						1,5,
						1,6,2,6,3,6,4,6,
						1,7,5,7,
						1,8,5,8,
						2,9,3,9,4,9}; 

unsigned char num7[] = {1,3,2,3,3,3,4,3,5,3,
						1,4,5,4,
						4,5,
						4,6,
						3,7,
						3,8,
						3,9};

unsigned char num8[] = {2,3,3,3,4,3,
						1,4,5,4,
						2,5,3,5,4,5,
						1,6,5,6,
						1,7,5,7,
						1,8,5,8,
						2,9,3,9,4,9};

unsigned char num9[] = {2,3,3,3,4,3,
						1,4,5,4,
						1,5,5,5,
						2,6,3,6,4,6,5,6,
						5,7,
						1,8,5,8,
						2,9,3,9,4,9};

unsigned char letA[] = {3,3,
						2,4,4,4,
						2,5,4,5,
						1,6,5,6,
						1,7,2,7,3,7,4,7,5,7,
						1,8,5,8,
						0,9,1,9,2,9,4,9,5,9,6,9};

unsigned char letB[] = {0,3,1,3,2,3,3,3,
						1,4,4,4,
						1,5,4,5,
						1,6,2,6,3,6,4,6,5,6,
						1,7,6,7,
						1,8,6,8,
						0,9,1,9,2,9,3,9,4,9,5,9};

unsigned char letC[] = {2,3,3,3,4,3,6,3,
						1,4,5,4,6,4,
						0,5,
						0,6,
						0,7,6,7,
						1,8,5,8,
						2,9,3,9,4,9};

unsigned char letD[] = {0,3,1,3,2,3,3,3,4,3,
						1,4,5,4,
						1,5,6,5,
						1,6,6,6,
						1,7,6,7,
						1,8,5,8,
						0,9,1,9,2,9,3,9,4,9};

unsigned char letE[] = {0,3,1,3,2,3,3,3,4,3,5,3,6,3,
						1,4,6,4,
						1,5,4,5,
						1,6,2,6,3,6,4,6,
						1,7,4,7,
						1,8,6,8,
						0,9,1,9,2,9,3,9,4,9,5,9,6,9};

unsigned char letF[] = {0,3,1,3,2,3,3,3,4,3,5,3,6,3,
						1,4,6,4,
						1,5,4,5,
						1,6,2,6,3,6,4,6,
						1,7,4,7,
						1,8,
						0,9,1,9,2,9};

unsigned char letG[] = {2,3,3,3,4,3,6,3,
						1,4,5,4,6,4,
						0,5,
						0,6,4,6,5,6,6,6,
						0,7,6,7,
						1,8,5,8,6,8,
						2,9,3,9,4,9,6,9};

unsigned char letH[] = {0,3,1,3,2,3,4,3,5,3,6,3,
						1,4,5,4,
						1,5,5,5,
						1,6,2,6,3,6,4,6,5,6,
						1,7,5,7,
						1,8,5,8,
						0,9,1,9,2,9,4,9,5,9,6,9};

unsigned char letI[] = {2,3,3,3,4,3,
						3,4,
						3,5,
						3,6,
						3,7,
						3,8,
						2,9,3,9,4,9};

unsigned char letJ[] = {3,3,4,3,5,3,
						4,4,
						4,5,
						4,6,
						0,7,4,7,
						0,8,4,8,
						1,9,2,9,3,9};

unsigned char letK[] = {0,3,1,3,2,3,4,3,5,3,6,3,
						1,4,5,4,
						1,5,4,5,
						1,6,2,6,3,6,
						1,7,4,7,
						1,8,5,8,
						0,9,1,9,2,9,4,9,5,9,6,9};

unsigned char letL[] = {0,3,1,3,2,3,
						1,4,
						1,5,
						1,6,
						1,7,
						1,8,6,8,
						0,9,1,9,2,9,3,9,4,9,5,9,6,9};

unsigned char letM[] = {0,3,1,3,5,3,6,3,
						1,4,2,4,4,4,5,4,
						1,5,3,5,5,5,
						1,6,3,6,5,6,
						1,7,5,7,
						1,8,5,8,
						0,9,1,9,2,9,4,9,5,9,6,9};

unsigned char letN[] = {0,3,1,3,4,3,5,3,6,3,
						1,4,2,4,5,4,
						1,5,3,5,5,5,
						1,6,3,6,5,6,
						1,7,3,7,5,7,
						1,8,4,8,5,8,
						0,9,1,9,2,9,5,9};

unsigned char letO[] = {2,3,3,3,4,3,
						1,4,5,4,
						0,5,6,5,
						0,6,6,6,
						0,7,6,7,
						1,8,5,8,
						2,9,3,9,4,9};

unsigned char letP[] = {0,3,1,3,2,3,3,3,4,3,5,3,
						1,4,6,4,
						1,5,6,5,
						1,6,2,6,6,6,
						1,7,3,7,4,7,5,7,
						1,8,
						0,9,1,9,2,9};

unsigned char letQ[] = {2,3,3,3,4,3,
						1,4,5,4,
						0,5,6,5,
						0,6,2,6,3,6,6,6,
						0,7,4,7,6,7,
						1,8,5,8,
						2,9,3,9,4,9,6,9};

unsigned char letR[] = {0,3,1,3,2,3,3,3,4,3,5,3,
						1,4,6,4,
						1,5,6,5,
						1,6,2,6,3,6,4,6,5,6,6,6,
						1,7,4,7,
						1,8,5,8,
						0,9,1,9,2,9,4,9,5,9,6,9};

unsigned char letS[] = { 1,3,2,3,3,3,4,3,6,3,
0,4,5,4,6,5,
0,5,
1,6,2,6,3,6,4,6,5,6,
6,7,
0,8,1,8,6,8,
0,9,2,9,3,9,4,9,5,9 };

unsigned char letT[] = { 0,3,1,3,2,3,3,3,4,3,5,3,6,3,
0,4,6,4,
3,5,
3,6,
3,7,
3,8,
2,9,3,9,4,9 };

unsigned char letU[] = { 0,3,1,3,2,3,4,3,5,3,6,3,
1,4,5,4,
1,5,5,5,
1,6,5,6,
1,7,5,7,
1,8,5,8,
2,9,3,9,4,9 };

unsigned char letV[] = { 0,3,1,3,2,3,4,3,5,3,6,3,
1,4,5,4,
1,5,5,5,
1,6,5,6,
2,7,4,7,
2,8,4,8,
3,9 };

unsigned char letW[] = { 0,3,1,3,2,3,4,3,5,3,6,3,
1,4,5,4,
1,5,5,5,
1,6,3,6,5,6,
1,7,3,7,5,7,
2,8,4,8,
2,9,4,9 };

unsigned char letX[] = { 0,3,1,3,2,3,4,3,5,3,6,3,
1,4,5,4,
2,5,4,5,
3,6,
2,7,4,7,
1,8,5,8,
0,9,1,9,2,9,4,9,5,9,6,9 };

unsigned char letY[] = { 0,3,1,3,2,3,4,3,5,3,6,3,
1,4,5,4,
2,5,4,5,
3,6,
3,7,
3,8,
2,9,3,9,4,9 };

unsigned char letZ[] = {0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3,
0, 4, 5, 4,
4, 5,
3, 6,
2, 7,
1, 8, 6, 8,
0, 9, 1, 9, 2, 9, 3, 9, 4, 9, 5, 9, 6, 9};

const unsigned char charDot[] = {2, 8, 3, 8,
	2, 9, 3, 9};

const unsigned char charDash[] = { 1, 6, 2, 6, 3, 6, 4, 6, 5, 6};

C7_12_Serif::C7_12_Serif(){
	for(int i = 0; i < 256; ++i){
		itsLetters[i].corePxCnt = sizeof(defGlyph) / sizeof(unsigned char) / 2;
		itsLetters[i].corePxs = (tsPoint<unsigned char>*)defGlyph;
		itsLetters[i].outlinePxCnt = 0;
		itsLetters[i].heigth = 12;
		itsLetters[i].width = 7;
	}
	itsLetters['0'].corePxCnt = sizeof(num0) / sizeof(unsigned char) / 2;
	itsLetters['0'].corePxs = (tsPoint<unsigned char>*)num0;
	itsLetters['1'].corePxCnt = sizeof(num1) / sizeof(unsigned char) / 2;
	itsLetters['1'].corePxs = (tsPoint<unsigned char>*)num1;
	itsLetters['2'].corePxCnt = sizeof(num2) / sizeof(unsigned char) / 2;
	itsLetters['2'].corePxs = (tsPoint<unsigned char>*)num2;
	itsLetters['3'].corePxCnt = sizeof(num3) / sizeof(unsigned char) / 2;
	itsLetters['3'].corePxs = (tsPoint<unsigned char>*)num3;
	itsLetters['4'].corePxCnt = sizeof(num4) / sizeof(unsigned char) / 2;
	itsLetters['4'].corePxs = (tsPoint<unsigned char>*)num4;
	itsLetters['5'].corePxCnt = sizeof(num5) / sizeof(unsigned char) / 2;
	itsLetters['5'].corePxs = (tsPoint<unsigned char>*)num5;
	itsLetters['6'].corePxCnt = sizeof(num6) / sizeof(unsigned char) / 2;
	itsLetters['6'].corePxs = (tsPoint<unsigned char>*)num6;
	itsLetters['7'].corePxCnt = sizeof(num7) / sizeof(unsigned char) / 2;
	itsLetters['7'].corePxs = (tsPoint<unsigned char>*)num7;
	itsLetters['8'].corePxCnt = sizeof(num8) / sizeof(unsigned char) / 2;
	itsLetters['8'].corePxs = (tsPoint<unsigned char>*)num8;
	itsLetters['9'].corePxCnt = sizeof(num9) / sizeof(unsigned char) / 2;
	itsLetters['9'].corePxs = (tsPoint<unsigned char>*)num9;
	itsLetters['A'].corePxCnt = sizeof(letA) / sizeof(unsigned char) / 2;
	itsLetters['A'].corePxs = (tsPoint<unsigned char>*)letA;
	itsLetters['B'].corePxCnt = sizeof(letB) / sizeof(unsigned char) / 2;
	itsLetters['B'].corePxs = (tsPoint<unsigned char>*)letB;
	itsLetters['C'].corePxCnt = sizeof(letC) / sizeof(unsigned char) / 2;
	itsLetters['C'].corePxs = (tsPoint<unsigned char>*)letC;
	itsLetters['D'].corePxCnt = sizeof(letD) / sizeof(unsigned char) / 2;
	itsLetters['D'].corePxs = (tsPoint<unsigned char>*)letD;
	itsLetters['E'].corePxCnt = sizeof(letE) / sizeof(unsigned char) / 2;
	itsLetters['E'].corePxs = (tsPoint<unsigned char>*)letE;
	itsLetters['F'].corePxCnt = sizeof(letF) / sizeof(unsigned char) / 2;
	itsLetters['F'].corePxs = (tsPoint<unsigned char>*)letF;
	itsLetters['G'].corePxCnt = sizeof(letG) / sizeof(unsigned char) / 2;
	itsLetters['G'].corePxs = (tsPoint<unsigned char>*)letG;
	itsLetters['H'].corePxCnt = sizeof(letH) / sizeof(unsigned char) / 2;
	itsLetters['H'].corePxs = (tsPoint<unsigned char>*)letH;
	itsLetters['I'].corePxCnt = sizeof(letI) / sizeof(unsigned char) / 2;
	itsLetters['I'].corePxs = (tsPoint<unsigned char>*)letI;
	itsLetters['J'].corePxCnt = sizeof(letJ) / sizeof(unsigned char) / 2;
	itsLetters['J'].corePxs = (tsPoint<unsigned char>*)letJ;
	itsLetters['K'].corePxCnt = sizeof(letK) / sizeof(unsigned char) / 2;
	itsLetters['K'].corePxs = (tsPoint<unsigned char>*)letK;
	itsLetters['L'].corePxCnt = sizeof(letL) / sizeof(unsigned char) / 2;
	itsLetters['L'].corePxs = (tsPoint<unsigned char>*)letL;
	itsLetters['M'].corePxCnt = sizeof(letM) / sizeof(unsigned char) / 2;
	itsLetters['M'].corePxs = (tsPoint<unsigned char>*)letM;
	itsLetters['N'].corePxCnt = sizeof(letN) / sizeof(unsigned char) / 2;
	itsLetters['N'].corePxs = (tsPoint<unsigned char>*)letN;
	itsLetters['O'].corePxCnt = sizeof(letO) / sizeof(unsigned char) / 2;
	itsLetters['O'].corePxs = (tsPoint<unsigned char>*)letO;
	itsLetters['P'].corePxCnt = sizeof(letP) / sizeof(unsigned char) / 2;
	itsLetters['P'].corePxs = (tsPoint<unsigned char>*)letP;
	itsLetters['Q'].corePxCnt = sizeof(letQ) / sizeof(unsigned char) / 2;
	itsLetters['Q'].corePxs = (tsPoint<unsigned char>*)letQ;
	itsLetters['R'].corePxCnt = sizeof(letR) / sizeof(unsigned char) / 2;
	itsLetters['R'].corePxs = (tsPoint<unsigned char>*)letR;
	itsLetters['S'].corePxCnt = sizeof(letS) / sizeof(unsigned char) / 2;
	itsLetters['S'].corePxs = (tsPoint<unsigned char>*)letS;
	itsLetters['T'].corePxCnt = sizeof(letT) / sizeof(unsigned char) / 2;
	itsLetters['T'].corePxs = (tsPoint<unsigned char>*)letT;
	itsLetters['U'].corePxCnt = sizeof(letU) / sizeof(unsigned char) / 2;
	itsLetters['U'].corePxs = (tsPoint<unsigned char>*)letU;
	itsLetters['V'].corePxCnt = sizeof(letV) / sizeof(unsigned char) / 2;
	itsLetters['V'].corePxs = (tsPoint<unsigned char>*)letV;
	itsLetters['W'].corePxCnt = sizeof(letW) / sizeof(unsigned char) / 2;
	itsLetters['W'].corePxs = (tsPoint<unsigned char>*)letW;
	itsLetters['X'].corePxCnt = sizeof(letX) / sizeof(unsigned char) / 2;
	itsLetters['X'].corePxs = (tsPoint<unsigned char>*)letX;
	itsLetters['Y'].corePxCnt = sizeof(letY) / sizeof(unsigned char) / 2;
	itsLetters['Y'].corePxs = (tsPoint<unsigned char>*)letY;
	itsLetters['Z'].corePxCnt = sizeof(letZ) / sizeof(unsigned char) / 2;
	itsLetters['Z'].corePxs = (tsPoint<unsigned char>*)letZ;

	itsLetters[' '].corePxCnt = 0;
	itsLetters[' '].corePxs = (tsPoint<unsigned char>*)0;
	itsLetters['.'].corePxCnt = sizeof(charDot) / sizeof(unsigned char) / 2;
	itsLetters['.'].corePxs = (tsPoint<unsigned char>*)charDot;
	itsLetters['-'].corePxCnt = sizeof(charDash) / sizeof(unsigned char) / 2;
	itsLetters['-'].corePxs = (tsPoint<unsigned char>*)charDash;
}

tsLetterGlyph* C7_12_Serif::getLetter(unsigned char letter){
	return itsLetters + letter;
}