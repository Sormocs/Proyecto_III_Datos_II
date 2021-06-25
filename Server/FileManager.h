//
// Created by luis on 24/6/21.
//

#ifndef SERVER_FILEMANAGER_H
#define SERVER_FILEMANAGER_H

#include <iostream>
#include <fstream>
#include "json.hpp"
#include <iomanip>
#include "tinyxml2.h"

using json = nlohmann::json;
using namespace tinyxml2;
using namespace std;

class FileManager {

public:

    void Write(std::string text, std::string path);
    std::string Read(std::string path);

    void WriteJson(json obj, std::string path);
    json ReadJson(std::string path);

    void GenerateXML();
    std::string GetPath(std::string node);
    std::string GetIP(std::string node);
    std::string GetPort(std::string node);
};


#endif //SERVER_FILEMANAGER_H
