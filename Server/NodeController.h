//
// Created by luis on 24/6/21.
//

#ifndef SERVER_NODECONTROLLER_H
#define SERVER_NODECONTROLLER_H
#include "FileManager.h"
#include "ListDiskNode.h"
#include "BytesConverter.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class NodeController {

public:

    bool activeDisk1 = true;
    bool activeDisk2 = true;

    ListDiskNode *listNodes = new ListDiskNode();
    FileManager *file = new FileManager();
    BytesConverter *converter = new BytesConverter();

    string path1 = file->GetPath("Node1");
    string path2 = file->GetPath("Node2");
    string path3 = file->GetPath("Node3");

    NodeController();

    void SaveFile(string text, string path);
    void DeleteFile(string name);
    void ConfigMetada(string name, string path, int bytes);
    void DeleteMetada(string name, string path, int bytes);

    json ReadRaid(string name);
    string ReadBook(string name);
    string WithoutParity(string name);
    string ParityDisk1(string name);
    string ParityDisj2(string name);

    bool CheckMemory(string search, string name);
    json CheckSpace();

    bool ChangeDisk1();
    bool ChangeDisk2();

    bool VerifyMetada(string name);


};


#endif //SERVER_NODECONTROLLER_H
