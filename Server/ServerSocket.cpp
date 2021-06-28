/**
 * @file ServerSocket.cpp
 * @brief Definicion de los metodos de la clase ServerSocket
 */
#include "ServerSocket.h"
//#include "Huffman.h"

ServerSocket* ServerSocket::instance = nullptr;

ServerSocket::ServerSocket() {
    nodeController = new NodeController;
}

/**
 * @brief Get instance from server socket
 * @return serversocket*
 */

ServerSocket *ServerSocket::getInstance() {
    if(instance == nullptr){
        instance = new ServerSocket;
    }
    return instance;
}

/**
 * @brief start server
 */

void ServerSocket::Start() {listening = socket(AF_INET, SOCK_STREAM,0);
    if (listening == -1)
    {
        std::cerr << "Can't create a socket! Quitting" << std::endl;
        exit(-1);
    }

    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

    std::cout << "Server Running" << std::endl;

    clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        std::cout << host << " connected on port " << service << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
    }

    // Close listening socket
    close(listening);

    while (true)
    {
        memset(buf, 0, 4096);

        // Wait for client to send data
        bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cerr << "Error in recv(). Quitting" << std::endl;
            break;
        }

        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected " << std::endl;
            break;
        }

//        std::string received = Huffman::getInstance()->Decode(std::string(buf,bytesReceived));
        std::string received = std::string(buf,bytesReceived);
        std::cout << "From Client: " << received;

        if (received == "end") return;

        json jReceived = json::parse(received);

        if (jReceived["DISCONNECT"].get<std::string>() != "NO") {
            if (jReceived["DISCONNECT"].get<std::string>() == "DISC1") {

                json temporal = json();

                if (nodeController->ChangeDisk1())
                    temporal["DISC_STATE"]["DISC1"] = true;

                else
                    temporal["DISC_STATE"]["DISC1"] = false;

                Send(temporal.dump());
            }

            else if (jReceived["DISCONNECT"].get<std::string>() == "DISC2") {

                json temporal = json();
                temporal["DISC_STATE"]["DISC2"] = nodeController->ChangeDisk2();
                Send("disconnected");
            }

        } if (jReceived["ADD_FILE"]["NAME"].get<std::string>() != "NO") {
            nodeController->SaveFile(jReceived["ADD_FILE"]["CONTENT"].get<std::string>(),jReceived["ADD_FILE"]["NAME"].get<std::string>());
            json temporal = json();
            temporal["SAVED"] = true;
            Send("saved");
        }

        if (jReceived["READ_FILE"].get<std::string>() != "NO"){

            json temporal = json();
//            temporal["DATA"] = nodeController->ReadBook(jReceived["READ_FILE"].get<std::string>());
            Send(nodeController->ReadBook(jReceived["READ_FILE"].get<std::string>()));
        }

        if (jReceived["SEARCH_FILE"].get<std::string>() != "NO") {

            printf("%s", nodeController->ReadRaid(jReceived["SEARCH_FILE"].get<std::string>()).dump(4).c_str());
            Send(nodeController->ReadRaid(jReceived["SEARCH_FILE"].get<std::string>()).dump());
        }

        if (jReceived["DELETE_FILE"].get<std::string>() != "NO") {

            nodeController->DeleteFile(jReceived["DELETE_FILE"].get<std::string>());

            json temporal = json();
            temporal["DELETED"] = true;
            Send("deleted");
        }

        if (jReceived["UPDATE"].get<std::string>() != "NO") {

            json temporal = json();

            temporal["Node1"]["Used"] = std::to_string(1073741824 - nodeController->CheckSpace()["Node1"].get<int>());
            temporal["Node1"]["Available"] = std::to_string(nodeController->CheckSpace()["Node1"].get<int>());

            temporal["Node2"]["Used"] = std::to_string(1073741824 - nodeController->CheckSpace()["Node2"].get<int>());
            temporal["Node2"]["Available"] = std::to_string(nodeController->CheckSpace()["Node2"].get<int>());

            temporal["Node3"]["Used"] = std::to_string(1073741824 - nodeController->CheckSpace()["Node3"].get<int>());
            temporal["Node3"]["Available"] = std::to_string(nodeController->CheckSpace()["Node3"].get<int>());

            Send(temporal.dump());
        }

        if (jReceived["END"].get<bool>()) return;
    }

    close(clientSocket);
}

/**
 * @brief send msg
 * @param msg string
 */

void ServerSocket::Send(std::string msg) {

//    std::string new_msg = Huffman::getInstance()->GetFreqs(msg);
    send(clientSocket, msg.c_str(),msg.length(),0);
}
