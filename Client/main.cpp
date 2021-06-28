#include "ClientSock.h"
#include "Interface.h"

void Graphics(int argc, char *argv[]) {
    SetInstance(new UI(argc, argv));
    Run();
}

void RunClient(){

    ClientSock::getInstance()->Start();
}

int main(int argc, char *argv[]) {



    std::thread RunGraphics(Graphics, argc, argv);

    std::thread RunC(RunClient);

    RunGraphics.join();

    RunC.join();

    return 0;
}
