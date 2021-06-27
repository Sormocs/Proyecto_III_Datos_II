/**
 * @file Client.h
 * @brief Declaracion de los metodos de la clase ClientSock.
 */
#include "ClientSock.h"
#include "Huffman.h"

ClientSock* ClientSock::instance = nullptr;

ClientSock *ClientSock::getInstance() {
    if (instance == nullptr){
        instance = new ClientSock;
    }
    return instance;
}

void ClientSock::Start() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        exit(1);
    }

    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        exit(1);
    }

    bool run = true;
    while (run){
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cout << "Error getting response" << std::endl;
        }
        else {

            //		Display response
            std::string temp = std::string(buf, bytesReceived);
            sleep(0.5);
            this->received = Huffman::getInstance()->Decode(temp);

            std::cout << "From Server:" << received << std::endl;
        }
    }
    close(sock);
    exit(0);
}

using namespace std::literals::chrono_literals;
void ClientSock::Send(std::string msg) {
    std::string new_msg = Huffman::getInstance()->GetFreqs(msg);
    std::this_thread::sleep_for(0.15s);
    int sendRes = send(sock, msg.c_str(), msg.length(), 0);
    if (sendRes == -1) {
        std::cout << "Send message failed" << std::endl;
    }
}

std::string ClientSock::GetReceived() {

    std::string temp = received;
    this->received = "";
    return temp;
}
