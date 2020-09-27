#ifndef COLORS_H
#define COLORS_H

class CRGB{
public:
	CRGB(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0);

	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();
	unsigned char getGray();

	void setRed(unsigned char value);
	void setGreen(unsigned char value);
	void setBlue(unsigned char value);

	bool operator==(const CRGB& other);
	bool isGrayScale();
private:
	unsigned char m_blue;
	unsigned char m_green;
	unsigned char m_red;
	
};


#endif