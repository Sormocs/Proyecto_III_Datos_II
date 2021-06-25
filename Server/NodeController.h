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

    ListDiskNode *listNodes = new ListDiskNode();
    FileManager *file = new FileManager();
    BytesConverter *converter = new BytesConverter();

    string path1 = file->GetPath("Node1");
    string path2 = file->GetPath("Node2");
    string path3 = file->GetPath("Node3");

    NodeController();
    void SaveFile(string text, string path);
    void ConfigMetada(string name, string path, int bytes);



};


#endif //SERVER_NODECONTROLLER_H
