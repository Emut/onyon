#pragma once
#include "CFont.h"


class CFontFactory {
public:
	static IFont* getFont(const char* fontName, int size);
};