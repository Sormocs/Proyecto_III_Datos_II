#include <iostream>
#include <pthread.h>
#include "ServerSocket.h"

void RunServer(){

    ServerSocket::getInstance()->Start();

}

int main(){

    std::thread RunS(RunServer);

    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(8.15s);
    ServerSocket::getInstance()->Send("This#is#a#message");

    RunS.join();

    return 0;
}
