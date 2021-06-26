#include "NodeController.h"


using namespace std;



int main() {

    NodeController *controller = new NodeController();

    cout << controller->ReadRaid("hola").dump(4);

}