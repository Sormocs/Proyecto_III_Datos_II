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