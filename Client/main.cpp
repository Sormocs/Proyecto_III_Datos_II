#include "ClientSock.h"
#include "Interface.h"

void Graphics() {
    Run();
}

void RunClient(){

    ClientSock::getInstance()->Start();
}

int main(int argc, char *argv[]) {

    std::thread Instance(SetInstance, new UI(argc, argv));
    Instance.join();


    std::thread RunGraphics(Graphics);

    std::thread RunC(RunClient);

    RunGraphics.join();

//    RunC.join();

    return 0;
}
