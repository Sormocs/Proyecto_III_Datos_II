/**
 * @file GUI.h contiene declaraciones de métodos y atributos de la interfaz gráfica.
 */

#include <thread>
#include "Button.h"
#include "SFMLTools.h"

using namespace sf;
/**
 * @brief Clase GUI se encarga de la interfaz gráfica.
 */
class GUI {
private:
    int16_t mouse[2] = {0, 0};
    int16_t size[2];
    int8_t mouseControl;
    Image icon;
    RenderWindow* window;

    void MainScreen();

    void Fill(Color color);

public:
    GUI(const int& width = 1000, const int& height = 650, const std::string& title = "ni idea");
    void Mainloop();
};