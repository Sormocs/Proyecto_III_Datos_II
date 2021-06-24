/**
 * @file ServerSocket.h
 * @author Sergio MB
 * @brief Contiene declaracion de clase Server
 */

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "thread"

#pragma once

/**
 * @brief Clase ServerSOcket que delara los atributos y metodos de server de los sockets.
 */
class ServerSocket {
private:
    int listening;
    int PORT = 5000;
    int clientSocket;
    int bytesReceived;
    sockaddr_in hint;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    char buf[4096];

    static ServerSocket *instance;

    ServerSocket();

public:
    void Start();
    void Send(std::string msg);
    static ServerSocket* getInstance();
};
