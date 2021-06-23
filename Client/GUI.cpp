#include "GUI.h"

GUI::GUI(const int &width, const int &height, const std::string& title) {

    this->size[0] = (int16_t) width;
    this->size[1] = (int16_t) height;

    this->icon.loadFromFile("../Icons/icon.png"); // File/Image/Pixel

    this->mouseControl = 0;
}

void GUI::Mainloop() {

    this->window = new RenderWindow(VideoMode(size[0], size[1]), "T\xa2tulo", Style::Titlebar | Style::Close);

    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window->setPosition(Vector2i(0, 0));

    while (this->window->isOpen()) {

        Event event;

        this->mouse[0] = (int16_t) Mouse::getPosition(*window).x;
        this->mouse[1] = (int16_t) Mouse::getPosition(*window).y;

        if (MouseReleased(mouseControl)) printf("Soltado\n");
        if (MousePressed(mouseControl)) printf("Presionado\n");

        if (mouseControl & 1UL << 0 && mouseControl & 1UL << 1) {
            mouseControl = 0;
        }

        while (window->pollEvent(event)) {

            if (event.type == Event::Closed) {
                window->close();
            }

            if (event.type == Event::MouseButtonPressed) {
                this->mouseControl |= 1UL << 0;
            }
            if (event.type == Event::MouseButtonReleased){
                this->mouseControl |= 1UL << 1;
                this->mouseControl |= 0UL << 0;
            }
            if (event.type == Event::MouseMoved) {
                this->mouse[0] = (int16_t) Mouse::getPosition(*window).x;
                this->mouse[1] = (int16_t) Mouse::getPosition(*window).y;
            }
        }
//        window->clear();

        window->display();

        // 30 fps
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

}

void GUI::MainScreen() {

}

void GUI::Fill(Color color) {

    sf::RectangleShape bg = sf::RectangleShape(sf::Vector2f (1000,650));
    bg.setFillColor(sf::Color(150,150,100,255));
    bg.setPosition(0,0);
    window->draw(bg);
}
