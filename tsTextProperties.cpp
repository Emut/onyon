#include "tsTextProperties.h"

TextProperties::TextProperties() : pos(0, 0)
{
    text = NULL;
    isPosSetExt = false;
}

void TextProperties::setText(const char *text)
{
    if (this->text != NULL)
        delete[] this->text;

    this->text = new char[strlen(text)];
    strcpy(this->text, text);
}

char *TextProperties::getText()
{
    return text;
}