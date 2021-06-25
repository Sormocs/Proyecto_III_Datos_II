//
// Created by luis on 23/6/21.
//

#include "DiskNode.h"


DiskNode::DiskNode(std::string path) {

    this->path = path;
    back = nullptr;
    next = nullptr;
    FillPath();

}

DiskNode* DiskNode::GetBack() {
    return back;
}

DiskNode* DiskNode::GetNext() {
    return next;
}

void DiskNode::SetBack(DiskNode *node) {
    back = node;
}

void DiskNode::SetNext(DiskNode *node) {
    next = node;
}

ListPath* DiskNode::GetData() {
    return data;
}

void DiskNode::FillPath() {

    FileManager *file = new FileManager;

    json obj = file->ReadJson(path + "/metadata.json");

    int size = obj["amount"].get<int>();

    for (int i = 0; i < size; ++i) {

        data->AddFinal(obj["Archivos"][to_string(i)]["name"], obj["Archivos"][to_string(i)]["path"]);

    }

    delete file;

}
