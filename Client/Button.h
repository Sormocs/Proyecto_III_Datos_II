#include "SFMLTools.h"
#pragma once

using namespace sf;
class Button {
private:
    int16_t pos[2] = {0, 0};
    int16_t size[2] = {0, 0};
    std::string sText;

    Text* text;
    Font* font;
    Color* color;
    RectangleShape* area;
    int8_t buttonControllers;

    bool Over(int16_t* mouse);
    bool Clicked(int8_t mouseController);

public:
    Button(const int16_t& width, const int16_t& height, const std::string& string = std::string());
    void Draw(RenderWindow* window);
};