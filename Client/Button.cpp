//#include "Button.h"
//
//Button::Button(const int16_t& width, const int16_t& height, const std::string& string) {
//    size[0] = width;
//    size[1] = height;
//
//    sText = string;
//
//    text->setString(string);
//
//    font->loadFromFile("../Fonts/arial.ttf");
//
//    text->setCharacterSize(20);
//    text->setFont(*font);
//    text->setFillColor(black);
//
//    sf::RectangleShape figure(sf::Vector2f(width,height));
//    figure.setPosition(pos[0], pos[1]);
//    figure.setFillColor(defButtonCol1);
//    figure.setOutlineColor(black);
//    figure.setOutlineThickness(0.5);
//
//    text->setPosition(pos[0]+(width/2 - text->getLocalBounds().width/2), pos[1]+(height/2 - text->getLocalBounds().height/2));
//
//    this->area = &figure;
//}
//
//bool Button::Over(int16_t* mouse) {
//    if (ButtonEnable(buttonControllers)) {
//        if (pos[0] < mouse[0] && mouse[0] < pos[0] + size[0] && pos[1] < mouse[1] && mouse[1] < pos[1] + size[1]) {
//            area->setFillColor(defButtonCol2);
//            return true;
//
//        } else {
//            area->setFillColor(defButtonCol1);
//            return false;
//        };
//    }
//    return false;
//}
//
//bool Button::Clicked(int8_t mouseController) {
//
//    if (MousePressed(mouseController)) {
//
//        area->setFillColor(defButtonCol3);
//        return false;
//
//    } else if (MouseReleased(mouseController)) {
//        return true;
//
//    } else return false;
//}
//
//void Button::Draw(RenderWindow* window) {
//
//}
