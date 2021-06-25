//
// Created by luis on 24/6/21.
//


#include "FileManager.h"

void FileManager::Write(std::string text, std::string path) {

    std::ofstream ofs(path);
    if (ofs) {
        ofs << text << std::endl;
    }

}

std::string FileManager::Read(std::string path) {

    std::string temp;

    std::ifstream openPort1;
    openPort1.open(path);
    openPort1 >> temp;

    return temp;

}

void FileManager::WriteJson(json obj, std::string path) {

    std::ofstream o(path);
    o << std::setw(4) << obj << std::endl;

}

json FileManager::ReadJson(std::string path) {

    std::ifstream i(path);
    json j;
    i >> j;

    return j;

}