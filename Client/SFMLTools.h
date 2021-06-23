/**
* @file SFMLTools.h contiene deeclaración de constantes para la interfaz gráfica.
*/
#include <SFML/Graphics.hpp>

using namespace sf;

// Controles del ratón

#define MousePressed( byte ) ((byte) & 1UL << 0) ? true : false
#define MouseReleased(byte) ((byte) & 1UL << 1) ? true : false


// Controles de botón

#define ButtonEnable(byte) ((byte) & 1UL << 0) ? 1 : 0
#define ButtonPressed(byte) ((byte) & 1UL << 1) ? true : false
#define ButtonReleased(byte) ((byte) & 1UL << 2) ? true : false

// colores

Color black = Color(0, 0, 0);
Color defButtonCol1 = Color(175, 175, 175);
Color defButtonCol2 = Color(165, 165, 165);
Color defButtonCol3 = Color(150, 150, 150);
Color gris = Color(150,150,100);


/*
Shape RoundedRectangle(float x, float y, float rectWidth, float rectHeight, float radius, const sf::Color& Col, float Outline = 0.f, const sf::Color& OutlineCol = sf::Color(0, 0, 0), int POINTS=10)
{
	sf::Shape rrect = sf::Shape();
	rrect.SetOutlineWidth(Outline);
	float X=0,Y=0;
	for(int i=0; i<POINTS; i++)
	{
		X+=radius/POINTS;
		Y=sqrt(radius*radius-X*X);
		rrect.AddPoint(X+x+rectWidth-radius,y-Y+radius,Col,OutlineCol);
	}
	Y=0;
	for(int i=0; i<POINTS; i++)
	{
		Y+=radius/POINTS;
		X=sqrt(radius*radius-Y*Y);
		rrect.AddPoint(x+rectWidth+X-radius,y+rectHeight-radius+Y,Col,OutlineCol);
	}
	X=0;
	for(int i=0; i<POINTS; i++)
	{
		X+=radius/POINTS;
		Y=sqrt(radius*radius-X*X);
		rrect.AddPoint(x+radius-X,y+rectHeight-radius+Y,Col,OutlineCol);
	}
	Y=0;
	for(int i=0; i<POINTS; i++)
	{
		Y+=radius/POINTS;
		X=sqrt(radius*radius-Y*Y);
		rrect.AddPoint(x-X+radius,y+radius-Y,Col,OutlineCol);
	}
	return *rrect;

}
 */