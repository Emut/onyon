#ifndef FONT_7_12_SERIF_H
#define FONT_7_12_SERIF_H
//Taken from fontstruct.com/fontstructions/show/243645/7_12_serif at 2020 02 25
//This amazing font is created and licensed under creative commons by Christian Munk (CMunk)

#include "CFont.h"

class C7_12_Serif: public IFont{
public:
	C7_12_Serif();
	tsLetterGlyph* getLetter(unsigned char letter); 

};



#endif