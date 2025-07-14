#include "LineDisplay.hpp"

using namespace rack;

void LineDisplay::process() {
    darkenAll();

	// TODO: there has to be a way to write this that doesn't use 4 switch statements
	switch (*output1Index) {
		case 0:
			if (*in1connected) {
				drawLine(0, 5, numPixelsX, 5);
			}
			break;
		case 1:
			if (*in2connected) {
				drawLine(0, 25, numPixelsX, 5);
			}
			break;
		case 2:
			if (*in3connected) {
				drawLine(0, 45, numPixelsX, 5);
			}
			break;
		case 3:
			if (*in4connected) {
				drawLine(0, 65, numPixelsX, 5);
			}
			break;
	}

	switch (*output2Index) {
		case 0:
			if (*in1connected) {
				drawLine(0, 5, numPixelsX, 25);
			}
			break;
		case 1:
			if (*in2connected) {
				drawLine(0, 25, numPixelsX, 25);
			}
			break;
		case 2:
			if (*in3connected) {
				drawLine(0, 45, numPixelsX, 25);
			}
			break;
		case 3:
			if (*in4connected) {
				drawLine(0, 65, numPixelsX, 25);
			}
			break;
	}

	switch (*output3Index) {
		case 0:
			if (*in1connected) {
				drawLine(0, 5, numPixelsX, 45);
			}
			break;
		case 1:
			if (*in2connected) {
				drawLine(0, 25, numPixelsX, 45);
			}
			break;
		case 2:
			if (*in3connected) {
				drawLine(0, 45, numPixelsX, 45);
			}
			break;
		case 3:
			if (*in4connected) {
				drawLine(0, 65, numPixelsX, 45);
			}
			break;
	}

	switch (*output4Index) {
		case 0:
			if (*in1connected) {
				drawLine(0, 5, numPixelsX, 65);
			}
			break;
		case 1:
			if (*in2connected) {
				drawLine(0, 25, numPixelsX, 65);
			}
			break;
		case 2:
			if (*in3connected) {
				drawLine(0, 45, numPixelsX, 65);
			}
			break;
		case 3:
			if (*in4connected) {
				drawLine(0, 65, numPixelsX, 65);
			}
			break;
	}
}

void LineDisplay::drawLine(int x1, int y1, int x2, int y2) {
	// uses EEFLA, based off https://stackoverflow.com/questions/10060046/drawing-lines-with-bresenhams-line-algorithm
	bool yLonger=false;
    int shortLen=y2-y1;
    int longLen=x2-x1;
    if (abs(shortLen)>abs(longLen)) {
        std::swap(shortLen, longLen);
        yLonger=true;
    }
    int decInc = longLen==0 ?  decInc=0 : ((shortLen << 16) / longLen);

    if (yLonger) {
        y1*=numPixelsY;
        y2*=numPixelsY;
        if (longLen>0)
            for (int j=0x8000+(x1<<16);y1<=y2;y1+=numPixelsY, j+=decInc)
				lightPixel((j >> 16) % numPixelsX, y1/numPixelsY, 0, 0);
        else
            for (int j=0x8000+(x1<<16);y1>=y2;y1-=numPixelsY, j-=decInc)
				lightPixel((j >> 16) % numPixelsX, y1/numPixelsY, 0, 0);

    }
    else
    {
        if (longLen>0)
            for (int j=0x8000+(y1<<16);x1<=x2;++x1, j+=decInc)
				lightPixel(x1, (j >> 16) % numPixelsY, 0, 0);
        else
            for (int j=0x8000+(y1<<16);x1>=x2;--x1, j-=decInc)
				lightPixel(x1, (j >> 16) % numPixelsY, 0, 0);
    }
}
