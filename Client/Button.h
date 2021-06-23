#include <SFML/Graphics.hpp>

using namespace sf;
class Button {
private:
    int16_t pos[2];
    int16_t size[2];
    std::string sText;

    Text* text;
    Font* font;
    Color* color;
    RectangleShape* area;
    int8_t buttonControllers;
};