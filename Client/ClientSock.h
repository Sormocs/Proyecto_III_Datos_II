/**
 * @file Client.h
 * @author Sergio MB
 * @brief Declaracion de la clase ClientSock, que permite la conexion por medio de sockets con el servidor.
 */
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>

#pragma once

/**
 * @brief Clase cliente que crea el socket que se conecta a un host.
 */
class ClientSock {
private:
    int sock;
    int port = 5000;
    int connectRes;
    sockaddr_in hint;
    std::string ipAddress = "127.0.0.1";
    char buf[4092];
    static ClientSock *instance;
    std::string received;
    ClientSock() = default;

public:
    static ClientSock* getInstance();
    void Start();
    void Send(std::string msg);
    std::string GetReceived();
};




