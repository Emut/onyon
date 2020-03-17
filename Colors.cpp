#include "Colors.h"

CRGB::CRGB(unsigned char red, unsigned char green, unsigned char blue): m_red(red), m_green(green), m_blue(blue){

}

unsigned char CRGB::getRed(){return m_red;}
unsigned char CRGB::getGreen(){return m_green;}
unsigned char CRGB::getBlue(){return m_blue;}
unsigned char CRGB::getGray(){return (m_red + m_blue + m_green)/3;} //this truncates, not rounds to nearest gray value.

void CRGB::setRed(unsigned char value){m_red = value;}
void CRGB::setGreen(unsigned char value){m_green = value;}
void CRGB::setBlue(unsigned char value){m_blue = value;}