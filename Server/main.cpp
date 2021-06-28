#include <iostream>
#include <pthread.h>
#include "ServerSocket.h"
#include "NodeController.h"
#include "thread"

void RunServer(){

    ServerSocket::getInstance()->Start();

}

int main(){

//    NodeController* asd = new NodeController;
//
//    printf("%s", asd->CheckSpace().dump().c_str());

    std::thread RunS(RunServer);

    RunS.join();

    return 0;
}
