#include "CFontFactory.h"
#include <string.h>

#include "CFont_7_12_Serif.h"

IFont* CFontFactory::getFont(const char* fontName, int size) {
	if (strcmp(fontName, "7_12_Serif") == 0) {
		static IFont* itsFont = new C7_12_Serif();
		return itsFont;
	}
	else
		return NULL;
}