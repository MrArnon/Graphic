#ifndef HELLO_H
#define HELLO_H

#include "Figure.h"


class Hello : public Figure
{
public:

	Hello(int size=40, int offsetX=150, int offsetY=150) : Figure(size, offsetX, offsetY)
	{
	}
	 void Draw(HDC dc)
	{
		Ellipse( dc, offsetX-size, offsetY-size, offsetX+size, offsetY+size);
		//Pen->Color=clBlue;
		Arc(dc,offsetX-size,offsetY-size,offsetX+size,offsetY-size, offsetX-size/2,offsetY-size/2,offsetX+size/2,offsetY+size/2  );
		//Graphic::DrawArc(0,0,45.0F,270.0F);

	}
		bool InnerPoint(int X, int Y)
	{
	 return (X-offsetX)*(X-offsetX)+(Y-offsetY)*(Y-offsetY)<=size*size;;
	}

};

#endif HELLO_H
