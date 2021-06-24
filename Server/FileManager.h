//
// Created by luis on 24/6/21.
//

#ifndef SERVER_FILEMANAGER_H
#define SERVER_FILEMANAGER_H

#include <iostream>
#include <fstream>

using namespace std;

class FileManager {

public:

    void Write(std::string text, std::string path);
    std::string Read(std::string path);

};


#endif //SERVER_FILEMANAGER_H
